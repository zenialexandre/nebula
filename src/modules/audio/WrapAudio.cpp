#include "WrapAudio.hpp"

namespace nebula {

#define audio()(ModuleRegistry::getInstance<audio::Audio>(AUDIO))

    namespace audio {

int w_setDevice(lua_State *L) {
    deviceID devId = (deviceID) luaL_checknumber(L, 1);
    audio()->setDevice(devId);
    return 0;
}

int w_closeDevice(lua_State *L) {
    deviceID devId = (deviceID) luaL_checknumber(L, 1);
    audio()->closeDevice();
    return 0;
}

int w_getCurrentDevice(lua_State *L) {
    std::string devName = audio()->getCurrentDevice();
    lua_pushstring(L, devName.c_str());
    return 1;
}

int w_getCurrentDeviceID(lua_State *L) {
    deviceID devId = audio()->getCurrentDeviceID();
    lua_pushinteger(L, devId);
    return 1;
}

int w_getPlaybackDevices(lua_State *L) {
    std::vector<deviceID> devices = audio()->getPlaybackDevices();
    lua_createtable(L, devices.size(), 0);
    for (int i = 0; i < devices.size(); i++) {
        lua_pushinteger(L, devices.at(i));
        lua_rawseti(L, -2, i);
    }
    return 1;
}

int w_getRecordingDevices(lua_State *L) {
    std::vector<deviceID> devices = audio()->getRecordingDevices();
    lua_createtable(L, devices.size(), 0);
    for (int i = 0; i < devices.size(); i++) {
        lua_pushinteger(L, devices.at(i));
        lua_rawseti(L, -2, i);
    }
    return 1;
}

int w_getDeviceName(lua_State *L) {
    deviceID devId = (deviceID) luaL_checknumber(L, 1);
    std::string devName = audio()->getDeviceName(devId);
    lua_pushstring(L, devName.c_str());
    return 1;
}

int w_newSource(lua_State *L) {
    std::string filePath = luaL_checkstring(L, 1);
    std::string filePathRelative = data::File::getRelativePath(filePath);
    int srcId = audio()->newSource(filePathRelative);
    lua_pushinteger(L, srcId);
    return 1;
}

int w_play(lua_State *L) {
    int count = lua_gettop(L);
    int srcId = luaL_checkinteger(L, 1);
    bool loop = false;
    if (count == 2) {
        luaL_checktype(L, 2, LUA_TBOOLEAN);
        loop = lua_toboolean(L, 2);
    }
    audio()->play(srcId, loop);
    return 0;
}

int w_pause(lua_State *L) {
    int srcId = luaL_checkinteger(L, 1);
    audio()->pause(srcId);
    return 0;
}

int w_stop(lua_State *L) {
    int srcId = luaL_checkinteger(L, 1);
    audio()->stop(srcId);
    return 0;
}

int w_getSourceLength(lua_State *L) {
    int srcId = luaL_checkinteger(L, 1);
    int length = audio()->getSourceLength(srcId);
    lua_pushinteger(L, length);
    return 1;
}

int w_setSourceVolume(lua_State *L) {
    int srcId = luaL_checkinteger(L, 1);
    float volume = (float) luaL_checknumber(L, 2);
    audio()->setSourceVolume(srcId, volume);
    return 0;
}

int w_getSourceVolume(lua_State *L) {
    int srcId = luaL_checkinteger(L, 1);
    float volume = audio()->getSourceVolume(srcId);
    lua_pushnumber(L, volume);
    return 1;
}

int w_isPaused(lua_State *L) {
    int srcId = luaL_checkinteger(L, 1);
    bool paused = audio()->isPaused(srcId);
    lua_pushboolean(L, paused);
    return 1;
}

int w_isPlaying(lua_State *L) {
    int srcId = luaL_checkinteger(L, 1);
    bool playing = audio()->isPlaying(srcId);
    lua_pushboolean(L, playing);
    return 1;
}

int w_destroySource(lua_State *L) {
    int srcId = luaL_checkinteger(L, 1);
    audio()->destroySource(srcId);
    return 0;
}

// int w_newSFX(lua_State *L) {
//     std::string filePath = luaL_checkstring(L, 1);
//     std::string filePathRelative = data::File::getRelativePath(filePath);
//     int sfxId = audio()->newSFX(filePathRelative);
//     lua_pushinteger(L, sfxId);
//     return 1;
// }

// int w_playSFX(lua_State *L) {
//     int sfxId = luaL_checkinteger(L, 1);
//     audio()->playSFX(sfxId);
//     return 0;
// }

// int w_getSFXLength(lua_State *L) {
//     int sfxId = luaL_checkinteger(L, 1);
//     int length = audio()->getSFXLength(sfxId);
//     lua_pushinteger(L, length);
//     return 1;
// }

// int w_isSFXPlaying(lua_State *L) {
//     int sfxId = luaL_checkinteger(L, 1);
//     bool playing = audio()->isSFXPlaying(sfxId);
//     lua_pushboolean(L, playing);
//     return 1;
// }

// int w_destroySFX(lua_State *L) {
//     int sfxId = luaL_checkinteger(L, 1);
//     audio()->destroySFX(sfxId);
//     return 0;
// }

int w_setVolume(lua_State *L) {
    float volume = (float) luaL_checknumber(L, 1);
    audio()->setVolume(volume);
    return 0;
}

int w_getVolume(lua_State *L) {
    float volume = audio()->getVolume();
    lua_pushnumber(L, volume);
    return 1;
}

static const luaL_Reg functions[] = {
    {"setDevice", w_setDevice},
    {"closeDevice", w_closeDevice},
    {"getCurrentDevice", w_getCurrentDevice},
    {"getCurrentDeviceID", w_getCurrentDeviceID},
    {"getPlaybackDevices", w_getPlaybackDevices},
    {"getRecordingDevices", w_getRecordingDevices},
    {"newSource", w_newSource},
    {"play", w_play},
    {"pause", w_pause},
    {"stop", w_stop},
    {"getSourceLength", w_getSourceLength},
    {"setSourceVolume", w_setSourceVolume},
    {"getSourceVolume", w_getSourceVolume},
    {"isPaused", w_isPaused},
    {"isPlaying", w_isPlaying},
    {"destroySource", w_destroySource},
    {"setVolume", w_setVolume},
    {"getVolume", w_getVolume},
    {0, 0}
};


extern "C" int nlua_audio(lua_State *L) {
    Audio *audio = audio();

    WrapModule wModule;
    wModule.module = audio;
    wModule.funcs = functions;
    wModule.types = nullptr;

    return registerModule(L, wModule);
}

} // audio
} // nebula
