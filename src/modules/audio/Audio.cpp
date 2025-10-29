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
    //SDL_InitSubSystem(SDL_INIT_AUDIO);
    initDevice();
}

Audio::~Audio() {
    closeDevice();
    //SDL_QuitSubSystem(SDL_INIT_AUDIO);
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

    SDL_SetAudioPostmixCallback(deviceId, audioCallback, this);
    SDL_ResumeAudioDevice(deviceId);
    return true;
}

void Audio::closeDevice() {
    for (auto& [id, src] : sources) {
        if (src->stream) {
            SDL_DestroyAudioStream(src->stream);
        }
        if (src->io) {
            SDL_CloseIO(src->io);
        }
    }
    sources.clear();

    // for (auto& [id, fx] : effects) {
    //     if (fx->buffer) {
    //         SDL_free(fx->buffer);
    //     }
    // }
    // effects.clear();

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
        for (int i = 0; i < count; i++) {
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
        for (int i = 0; i < count; i++) {
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
    AudioSource *src = new AudioSource();
    src->path = path;

    src->io = SDL_IOFromFile(path.c_str(), "rb");
    if (!src->io) {
        std::cout << "Failed to open audio file: " << path << std::endl;
        return -1;
    }

    Uint8* buffer = nullptr;
    Uint32 length = 0;
    if (!SDL_LoadWAV(path.c_str(), &src->spec, &buffer, &src->length)) {
        std::cerr << "Failed to load WAV: " << SDL_GetError() << std::endl;
        SDL_CloseIO(src->io);
        return -1;
    }

    src->stream = SDL_CreateAudioStream(&src->spec, &deviceSpec);
    if (!src->stream) {
        std::cerr << "Failed to create audio stream: " << SDL_GetError() << std::endl;
        SDL_free(buffer);
        SDL_CloseIO(src->io);
        return -1;
    }

    if (!SDL_BindAudioStream(deviceId, src->stream)) {
        std::cerr << "Failed to bind audio stream: " << SDL_GetError() << std::endl;
        SDL_DestroyAudioStream(src->stream);
        SDL_free(buffer);
        SDL_CloseIO(src->io);
        return -1;
    }

    SDL_PutAudioStreamData(src->stream, buffer, length);
    SDL_free(buffer);

    int id = nextSourceId++;
    src->id = id;
    sources[id] = src;
    return id;
}

// void Audio::play(int sourceId, bool loop) {
//     if (sources.count(sourceId) == 0) {
//         return;
//     }

//     auto& src = sources[sourceId];
//     SDL_LockAudioStream(src->stream);
    
//     src->paused = false;
//     src->playing = true;
//     src->loop = loop;

//     SDL_SeekIO(src->io, 0, SDL_IO_SEEK_SET);
//     SDL_ClearAudioStream(src->stream);
    
//     Uint8* buffer = nullptr;
//     Uint32 length = 0;
//     if (SDL_LoadWAV(src->path.c_str(), &src->spec, &buffer, &length)) {
//         SDL_PutAudioStreamData(src->stream, buffer, length);
//         SDL_free(buffer);
//     }

//     //if (SDL_GetAudioStreamQueued(src->stream) == 0) {
//     //    SDL_SeekIO(src->io, 0, SDL_IO_SEEK_SET);
//     //    
//     //    Uint8* buffer = nullptr;
//     //    Uint32 length = 0;
//     //    if (SDL_LoadWAV(src->path.c_str(), &src->spec, &buffer, &length)) {
//     //        SDL_PutAudioStreamData(src->stream, buffer, length);
//     //        SDL_free(buffer);
//     //    }
//     //}
    
//     SDL_UnlockAudioStream(src->stream);
// }

void Audio::play(int sourceId, bool loop) {
    if (sources.count(sourceId) == 0) {
        return;
    }

    auto& src = sources[sourceId];
    SDL_LockAudioStream(src->stream);
    
    SDL_ClearAudioStream(src->stream);
    SDL_SeekIO(src->io, 0, SDL_IO_SEEK_SET);
    
    src->paused = false;
    src->playing = true;
    src->loop = loop;
    
    Uint8* buffer = nullptr;
    Uint32 length = 0;
    if (SDL_LoadWAV(src->path.c_str(), &src->spec, &buffer, &length)) {
        SDL_PutAudioStreamData(src->stream, buffer, length);
        //debugStreamState(sourceId, src, "AFTER PLAY");
        SDL_free(buffer);
    }
    
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
    SDL_SeekIO(src->io, 0, SDL_IO_SEEK_SET);
    SDL_UnlockAudioStream(src->stream);
}

int Audio::getSourceLength(int sourceId) {
    if (sources.count(sourceId) == 0) {
        return 0;
    }

    auto& src = sources[sourceId];
    SDL_LockAudioStream(src->stream);
    int length = src->length;
    SDL_UnlockAudioStream(src->stream);
    return length;
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
    bool playing = src->playing && !src->paused;
    SDL_UnlockAudioStream(src->stream);
    return playing;
}

void Audio::destroySource(int sourceId) {
    if (sources.count(sourceId) == 0) {
        return;
    }
    
    auto& src = sources[sourceId];
    if (src->stream) {
        SDL_UnbindAudioStream(src->stream);
        SDL_DestroyAudioStream(src->stream);
    }
    if (src->io) {
        SDL_CloseIO(src->io);
    }
    sources.erase(sourceId);
}

// int Audio::newSFX(const std::string& path) {
//     SFXSource *fx = new SFXSource();
//     if (!SDL_LoadWAV(path.c_str(), &fx->spec, &fx->buffer, &fx->length)) {
//         std::cerr << "Failed to load effect: " << SDL_GetError() << "\n";
//         return -1;
//     }
//     int id = nextEffectId++;
//     fx->id = id;
//     effects[id] = fx;
//     return id;
// }

// void Audio::playSFX(int effectId, float volume) {
//     if (effects.count(effectId) == 0) {
//         return;
//     }

//     auto& fx = effects[effectId];
//     fx->playing = true;
//     fx->position = 0;
//     fx->volume = volume;
// }

// int Audio::getSFXLength(int effectId) {
//     if (effects.count(effectId) == 0) {
//         return 0;
//     }
//     return effects.at(effectId)->length;
// }

// bool Audio::isSFXPlaying(int effectId) {
//     if (effects.count(effectId) == 0) {
//         return false;
//     }
//     return effects.at(effectId)->playing;
// }

// void Audio::destroySFX(int effectId) {
//     if (effects.count(effectId) == 0) {
//         return;
//     }

//     auto& fx = effects[effectId];
//     if (fx->buffer) {
//         SDL_free(fx->buffer);
//     }
//     effects.erase(effectId);
// }

void Audio::setVolume(float volume) {
    masterVolume = volume;
    
    for (auto& [id, src] : sources) {
        SDL_SetAudioStreamGain(src->stream, src->volume * masterVolume);
    }
}

float Audio::getVolume() const {
    return masterVolume;
}

void Audio::audioCallback(void* userdata, const SDL_AudioSpec *spec, float *buffer, int buflen) {
    Audio* self = (Audio*)userdata;
    if (!self) {
        return;
    }
    self->mixAudio(spec, buffer, buflen);
}

void Audio::mixAudio(const SDL_AudioSpec* spec, float* buffer, int buflen) {
    for (auto& [id, src] : sources) {
        //debugStreamState(id, src, "UPDATE");
        if (!src->playing || src->paused)
            continue;

        int queued = SDL_GetAudioStreamQueued(src->stream);
        Sint64 pos = SDL_TellIO(src->io);
        Sint64 size = SDL_GetIOSize(src->io);

        bool atEOF = (pos >= size);
        bool empty = (queued == 0);

        if (atEOF && empty) {
            src->playing = false;
            SDL_ClearAudioStream(src->stream);
            SDL_FlushAudioStream(src->stream);
            SDL_SeekIO(src->io, 0, SDL_IO_SEEK_SET);
            //debugStreamState(id, src, "AFTER UPDATE");
            continue;
        }

        if (queued < spec->freq * spec->channels * sizeof(float) / 10) { // 100ms
            Uint8 bufferChunk[2048];
            int bytes = SDL_ReadIO(src->io, bufferChunk, sizeof(bufferChunk));

            if (bytes > 0) {
                SDL_PutAudioStreamData(src->stream, bufferChunk, bytes);
            } else if (bytes == 0 && src->loop) {
                SDL_ClearAudioStream(src->stream);
                SDL_FlushAudioStream(src->stream);
                SDL_SeekIO(src->io, 0, SDL_IO_SEEK_SET);

                Uint8 restartChunk[2048];
                int restartBytes = SDL_ReadIO(src->io, restartChunk, sizeof(restartChunk));
                if (restartBytes > 0)
                    SDL_PutAudioStreamData(src->stream, restartChunk, restartBytes);
            } else if (bytes <= 0) {
                src->playing = false;
                SDL_ClearAudioStream(src->stream);
                SDL_FlushAudioStream(src->stream);
                SDL_SeekIO(src->io, 0, SDL_IO_SEEK_SET);
            }
        }
        //debugStreamState(id, src, "AFTER UPDATE");
    }
}


// void Audio::mixAudio(const SDL_AudioSpec* spec, float* buffer, int buflen) {    
//     for (auto& [id, src] : sources) {
//         if (!src->playing || src->paused) {
//             continue;
//         }
        
//         int bytesPerSecond = spec->freq * spec->channels * sizeof(float);
//         int lowWaterMark = bytesPerSecond / 20; // 50ms

//         int queued = SDL_GetAudioStreamQueued(src->stream);
        
//         if (queued < lowWaterMark) {
//             Uint8 refill[8192];
//             int refillBytes = SDL_ReadIO(src->io, refill, sizeof(refill));
            
//             if (refillBytes > 0) {
//                 SDL_PutAudioStreamData(src->stream, refill, refillBytes);
//             } else {
//                 if (src->loop) {
//                     SDL_SeekIO(src->io, 0, SDL_IO_SEEK_SET);
//                     SDL_ClearAudioStream(src->stream);
                    
//                     Uint8* wavBuffer = nullptr;
//                     Uint32 wavLength = 0;
//                     if (SDL_LoadWAV(src->path.c_str(), &src->spec, &wavBuffer, &wavLength)) {
//                         SDL_PutAudioStreamData(src->stream, wavBuffer, wavLength);
//                         SDL_free(wavBuffer);
//                     } else {
//                         src->playing = false;
//                     }
//                 } else {
//                     if (queued == 0) {
//                         Uint8 testBuffer[1];
//                         Sint64 currentPos = SDL_TellIO(src->io);
//                         int testRead = SDL_ReadIO(src->io, testBuffer, 1);

//                         if (testRead == 0) {
//                             src->playing = false;
//                             SDL_SeekIO(src->io, 0, SDL_IO_SEEK_SET);
//                         } else {
//                             SDL_SeekIO(src->io, currentPos, SDL_IO_SEEK_SET);
//                             Uint8 refill[8192];
//                             int refillBytes = SDL_ReadIO(src->io, refill, sizeof(refill));
//                             if (refillBytes > 0) {
//                                 SDL_PutAudioStreamData(src->stream, refill, refillBytes);
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     // for (auto& [id, fx] : effects) {
//     //     if (!fx->playing) {
//     //         continue;
//     //     }
        
//     //     Uint32 remaining = fx->length - fx->position;
//     //     if (remaining == 0) {
//     //         fx->playing = false;
//     //         continue;
//     //     }
        
//     //     int samplesToMix = buflen;
//     //     int bytesPerSample = (SDL_AUDIO_BITSIZE(fx->spec.format) / 8) * fx->spec.channels;
//     //     int samplesAvailable = remaining / bytesPerSample;
        
//     //     if (samplesToMix > samplesAvailable) {
//     //         samplesToMix = samplesAvailable;
//     //     }
        
//     //     if (samplesToMix > 0) {
//     //         float* converted = (float*)(SDL_malloc(samplesToMix * sizeof(float)));
//     //         if (converted) {
//     //             if (fx->spec.format == SDL_AUDIO_U8) {
//     //                 const Uint8* source = fx->buffer + fx->position;
//     //                 for (int i = 0; i < samplesToMix; i++) {
//     //                     converted[i] = (source[i] - 128) / 128.0f;
//     //                 }
//     //             } else if (fx->spec.format == SDL_AUDIO_S16) {
//     //                 const Sint16* source = reinterpret_cast<const Sint16*>(fx->buffer + fx->position);
//     //                 for (int i = 0; i < samplesToMix; i++) {
//     //                     converted[i] = source[i] / 32768.0f;
//     //                 }
//     //             } else if (fx->spec.format == SDL_AUDIO_F32) {
//     //                 const float* source = reinterpret_cast<const float*>(fx->buffer + fx->position);
//     //                 SDL_memcpy(converted, source, samplesToMix * sizeof(float));
//     //             }
                
//     //             float volume = fx->volume * masterVolume;
//     //             for (int i = 0; i < samplesToMix; i++) {
//     //                 buffer[i] += converted[i] * volume;

//     //                 if (buffer[i] > 1.0f) buffer[i] = 1.0f;
//     //                 if (buffer[i] < -1.0f) buffer[i] = -1.0f;
//     //             }
                
//     //             SDL_free(converted);
                
//     //             fx->position += samplesToMix * bytesPerSample;
//     //         }
//     //     }
        
//     //     if (fx->position >= fx->length) {
//     //         fx->playing = false;
//     //         fx->position = 0;
//     //     }
//     //}
// }

} // audio
} // nebula
