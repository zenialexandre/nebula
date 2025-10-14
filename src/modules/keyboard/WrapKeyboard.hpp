#pragma once

#include "Keyboard.hpp"
#include "../common/WrapModule.hpp"
#include "../common/LuaBidings.hpp"

namespace nebula {
    namespace keyboard {

extern "C" int nlua_keyboard(lua_State *L);

} // keyboard    
} // nebula