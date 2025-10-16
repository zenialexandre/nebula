#pragma once

#include "Physics.hpp"
#include "../common/WrapModule.hpp"
#include "../common/LuaBidings.hpp"

namespace nebula {
    namespace physics {

extern "C" int nlua_physics(lua_State *L);

} // physics    
} // nebula
