#pragma once

#include "Mouse.hpp"
#include "../common/WrapModule.hpp"
#include "../common/LuaBidings.hpp"

namespace nebula {
    namespace mouse {

extern "C" int nlua_mouse(lua_State *L);

} // mouse
} // nebula
