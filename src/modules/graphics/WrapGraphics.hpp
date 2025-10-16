#pragma once

#include "Graphics.h"
#include "../data/File.hpp"
#include "../common/WrapModule.hpp"
#include "../common/LuaBidings.hpp"

namespace nebula {
    namespace graphics {

extern "C" int nlua_graphics(lua_State *L);

} // graphics    
} // nebula
