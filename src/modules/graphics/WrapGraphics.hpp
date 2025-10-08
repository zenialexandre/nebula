#pragma once

#include "Graphics.h"
#include "../common/WrapModule.hpp"
#include "../common/LuaBidings.hpp"

namespace nebula {
    namespace graphics {

extern "C" int nlua_graphics(lua_State *L);

} // graphics    
} // nebula
