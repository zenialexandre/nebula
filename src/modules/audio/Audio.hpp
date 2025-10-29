#pragma once

#include "../common/Module.hpp"
#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include <unordered_map>

namespace nebula {
    namespace audio {

// streamed audio (ex: music)
struct AudioSource {
    int id;
    SDL_AudioStream* stream = nullptr;
    SDL_IOStream* io = nullptr;
    SDL_AudioSpec spec{};
    Uint32 length = 0;
    bool playing = false;
    bool paused = false;
    bool loop = false;
    float volume = 1.0f;
    std::string path;
};

// loaded sound effect (short sfx)
// struct SFXSource {
//     int id;
//     SDL_AudioSpec spec{};
//     Uint8* buffer = nullptr;
//     Uint32 length = 0;
//     bool playing = false;
//     float volume = 1.0f;
//     Uint32 position = 0;
// };

typedef SDL_AudioDeviceID deviceID;

class Audio : public Module {
public:
    Audio();
    ~Audio();

    // device
    bool initDevice(const deviceID deviceIdParam = SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK);
    void closeDevice();
    void setDevice(const deviceID deviceIdParam);
    std::string getCurrentDevice() const;
    deviceID getCurrentDeviceID() const;
    std::vector<deviceID> getPlaybackDevices();
    std::vector<deviceID> getRecordingDevices();
    std::string getDeviceName(const deviceID deviceIdParam) const;

    // streaming
    int newSource(const std::string& path);
    void play(int sourceId, bool loop = false);
    void pause(int sourceId);
    void stop(int sourceId);
    int getSourceLength(int sourceId);
    void setSourceVolume(int sourceId, float volume);
    float getSourceVolume(int sourceId) const;
    bool isPaused(int sourceId);
    bool isPlaying(int sourceId);
    void destroySource(int sourceId);

    // sfx
    // int newSFX(const std::string& path);
    // void playSFX(int effectId, float volume = 1.0f);
    // int getSFXLength(int effectId);
    // bool isSFXPlaying(int effectId);
    // void destroySFX(int effectId);

    // master
    void setVolume(float volume);
    float getVolume() const;

private:
    static void audioCallback(void* userdata, const SDL_AudioSpec *spec, float *buffer, int buflen);
    void mixAudio(const SDL_AudioSpec* spec, float* buffer, int buflen);

    SDL_AudioDeviceID deviceId = 0;
    SDL_AudioSpec deviceSpec{};
    float masterVolume = 1.0f;

    // sources and sfxs
    std::unordered_map<int, AudioSource*> sources;
    //std::unordered_map<int, SFXSource*> effects;

    int nextSourceId = 1;
    //int nextEffectId = 1;
};

} // audio
} // nebula