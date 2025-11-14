#include "Audio.hpp"

#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_iostream.h>

#include <iostream>

namespace nebula {
    namespace audio {

static float bytesToSeconds(const SDL_AudioSpec& spec, int byteCount) {
    int bits = SDL_AUDIO_BITSIZE(spec.format);
    if (bits == 0 || spec.channels == 0 || spec.freq == 0) {
        return 0.0f;
    }
    int bytesPerSample = (bits / 8) * spec.channels;
    if (bytesPerSample == 0) {
        return 0.0f;
    }
    return (float)byteCount / (spec.freq * bytesPerSample);
}

Audio::Audio() : Module(AUDIO, "audio") {
    initDevice();
}

Audio::~Audio() {
    closeDevice();
}

bool Audio::initDevice(const deviceID deviceIdParam) {
    SDL_AudioSpec want{};
    want.freq = 48000;
    want.format = SDL_AUDIO_F32;
    want.channels = 2;

    deviceId = SDL_OpenAudioDevice(deviceIdParam, &want);
    if (!deviceId) {
        deviceId = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &want);

        if (!deviceId) {
            std::cout << "ERROR::AUDIO::OPENAUDIODEVICE: " << SDL_GetError() << std::endl;
            return false;
        }
    }

    SDL_GetAudioDeviceFormat(deviceId, &deviceSpec, nullptr);

    SDL_ResumeAudioDevice(deviceId);
    return true;
}

void Audio::closeDevice() {
    for (auto& [id, src] : sources) {
        if (src->stream) {
            SDL_UnbindAudioStream(src->stream);
            SDL_DestroyAudioStream(src->stream);
            SDL_free(src->buffer);
        }
        if (src->virtualDevice != deviceId) {
            SDL_CloseAudioDevice(src->virtualDevice);
        }
    }
    sources.clear();

    if (deviceId) {
        SDL_CloseAudioDevice(deviceId);
        deviceId = 0;
    }
}

//static void debugStreamState(int id, nebula::audio::AudioSource* src, const char* phase) {
//    if (id!=1) return;
//    int queued = SDL_GetAudioStreamQueued(src->stream);
//    int available = SDL_GetAudioStreamAvailable(src->stream);
//    Sint64 pos = src->io ? SDL_TellIO(src->io) : 0;
//    Sint64 size = src->io ? SDL_GetIOSize(src->io) : 0;
//
//    printf("[AUDIO %s] src=%d playing=%d loop=%d queued=%d avail=%d pos=%lld/%lld\n",
//           phase, id, src->playing, src->loop,
//           queued, available,
//           (long long)pos, (long long)size);
//}

void Audio::setDevice(const deviceID deviceIdParam) {
    closeDevice();
    initDevice(deviceIdParam);
}

std::string Audio::getCurrentDevice() const {
    return getDeviceName(deviceId);
}

deviceID Audio::getCurrentDeviceID() const {
    return deviceId;
}

std::vector<deviceID> Audio::getPlaybackDevices() {
    std::vector<deviceID> devices;
    int count = 0;
    SDL_AudioDeviceID *playbackDevices = SDL_GetAudioPlaybackDevices(&count);

    if (playbackDevices) {
        devices.reserve(count);
        for (size_t i = 0; i < count; ++i) {
            SDL_AudioDeviceID devId = playbackDevices[i];
            devices.emplace_back(devId);
        }
        SDL_free(playbackDevices);
    }

    return devices;
}


std::vector<deviceID> Audio::getRecordingDevices() {
    std::vector<deviceID> devices;
    int count = 0;
    SDL_AudioDeviceID *recordingDevices = SDL_GetAudioRecordingDevices(&count);

    if (recordingDevices) {
        devices.reserve(count);
        for (size_t i = 0; i < count; ++i) {
            SDL_AudioDeviceID devId = recordingDevices[i];
            devices.emplace_back(devId);
        }
        SDL_free(recordingDevices);
    }

    return devices;
}

std::string Audio::getDeviceName(const deviceID deviceIdParam) const {
    const char *name = SDL_GetAudioDeviceName(deviceIdParam);
    if (!name) {
        return std::string();
    }
    return std::string(name);
}

int Audio::newSource(const std::string& path) {
    SDL_AudioSpec want{};
    want.freq = 48000;
    want.format = SDL_AUDIO_F32;
    want.channels = 2;

    AudioSource *src = new AudioSource();
    src->path = path;

    Uint8* buffer = nullptr;
    if (!SDL_LoadWAV(path.c_str(), &src->spec, &buffer, &src->bufferLength)) {
        std::cerr << "Failed to load WAV: " << SDL_GetError() << std::endl;
        return -1;
    }

    src->buffer = buffer;
    buffer = nullptr;

    src->stream = SDL_CreateAudioStream(&src->spec, &deviceSpec);
    if (!src->stream) {
        std::cerr << "Failed to create audio stream: " << SDL_GetError() << std::endl;
        return -1;
    }

    src->virtualDevice = SDL_OpenAudioDevice(deviceId, &want);
    if (!src->virtualDevice) {
        src->virtualDevice = deviceId;
    }

    if (!SDL_BindAudioStream(src->virtualDevice, src->stream)) {
        std::cerr << "Failed to bind audio stream: " << SDL_GetError() << std::endl;
        SDL_DestroyAudioStream(src->stream);
        SDL_CloseAudioDevice(src->virtualDevice);
        return -1;
    }

    int id = nextSourceId++;
    src->id = id;
    sources[id] = src;
    return id;
}

void Audio::play(int sourceId, bool loop) {
    if (sources.count(sourceId) == 0) {
        return;
    }

    auto& src = sources[sourceId];
    SDL_LockAudioStream(src->stream);
    
    SDL_ClearAudioStream(src->stream);
    
    src->paused = false;
    src->playing = true;
    src->loop = loop;
    
    SDL_PutAudioStreamData(src->stream, src->buffer, src->bufferLength);
    
    SDL_UnlockAudioStream(src->stream);
    //std::cout << "Playing source " << sourceId << ", queued: " 
    //          << SDL_GetAudioStreamQueued(src->stream) << " bytes" << std::endl;
}

void Audio::pause(int sourceId) {
    if (sources.count(sourceId) == 0) {
        return;
    }
    SDL_LockAudioStream(sources[sourceId]->stream);

    sources[sourceId]->paused = true;
    SDL_PauseAudioStreamDevice(sources[sourceId]->stream);

    SDL_UnlockAudioStream(sources[sourceId]->stream);
}

void Audio::resume(int sourceId) {
    if (sources.count(sourceId) == 0) {
        return;
    }
    SDL_LockAudioStream(sources[sourceId]->stream);

    sources[sourceId]->paused = false;
    SDL_ResumeAudioStreamDevice(sources[sourceId]->stream);

    SDL_UnlockAudioStream(sources[sourceId]->stream);
}

void Audio::stop(int sourceId) {
    if (sources.count(sourceId) == 0) {
        return;
    }

    auto& src = sources[sourceId];
    SDL_LockAudioStream(src->stream);
    src->playing = false;
    src->paused = false;
    SDL_ClearAudioStream(src->stream);
    SDL_UnlockAudioStream(src->stream);
}

float Audio::getSourceLength(int sourceId) {
    if (sources.count(sourceId) == 0) {
        return 0;
    }
    double seconds = 0.0;
    auto& src = sources[sourceId];
    SDL_LockAudioStream(src->stream);

    seconds = bytesToSeconds(src->spec, src->bufferLength);

    SDL_UnlockAudioStream(src->stream);
    return seconds;
}

void Audio::setSourceVolume(int sourceId, float volume) {
    if (sources.count(sourceId) == 0) {
        return;
    }
    auto& src = sources[sourceId];
    SDL_LockAudioStream(src->stream);
    src->volume = volume;
    SDL_SetAudioStreamGain(src->stream, volume * masterVolume);
    SDL_UnlockAudioStream(src->stream);
}

float Audio::getSourceVolume(int sourceId) const {
    if (sources.count(sourceId) == 0) {
        return 0.0f;
    }
    const auto& src = sources.at(sourceId);
    SDL_LockAudioStream(src->stream);
    float volume = src->volume;
    SDL_UnlockAudioStream(src->stream);
    return volume;
}

bool Audio::isPaused(int sourceId) {
    if (sources.count(sourceId) == 0) {
        return false;
    }
    const auto& src = sources.at(sourceId);
    SDL_LockAudioStream(src->stream);
    bool paused = src->paused;
    SDL_UnlockAudioStream(src->stream);
    return paused;
}

bool Audio::isPlaying(int sourceId) {
    if (sources.count(sourceId) == 0) {
        return false;
    }
    const auto& src = sources.at(sourceId);
    SDL_LockAudioStream(src->stream);
    if (src->playing) {
        src->playing = SDL_GetAudioStreamAvailable(src->stream) != 0;
    }
    SDL_UnlockAudioStream(src->stream);
    return src->playing;
}

void Audio::destroySource(int sourceId) {
    if (sources.count(sourceId) == 0) {
        return;
    }
    
    auto& src = sources[sourceId];
    if (src->stream) {
        SDL_UnbindAudioStream(src->stream);
        SDL_DestroyAudioStream(src->stream);
        SDL_free(src->buffer);
    }
    if (src->virtualDevice != deviceId) {
        SDL_CloseAudioDevice(src->virtualDevice);
    }
    sources.erase(sourceId);
}

void Audio::setVolume(float volume) {
    masterVolume = volume;
    
    for (auto& [id, src] : sources) {
        SDL_SetAudioStreamGain(src->stream, src->volume * masterVolume);
    }
}

float Audio::getVolume() const {
    return masterVolume;
}

} // audio
} // nebula
