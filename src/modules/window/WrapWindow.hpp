#pragma once

#include "Window.h"
#include "../graphics/Graphics.h"
#include "../common/WrapModule.hpp"
#include "../common/LuaBidings.hpp"

namespace nebula {
    namespace window {

extern "C" int nlua_window(lua_State *L);

} // window    
} // nebula
