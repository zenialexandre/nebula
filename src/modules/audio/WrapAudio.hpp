#pragma once

#include "Audio.hpp"
#include "../data/File.hpp"
#include "../common/WrapModule.hpp"
#include "../common/LuaBidings.hpp"

namespace nebula {
    namespace audio {

extern "C" int nlua_audio(lua_State *L);

} // audio    
} // nebula