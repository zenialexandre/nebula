#pragma once

#include "../common/WrapType.hpp"
#include "../common/LuaBidings.hpp"
#include "Font.hpp"

#include <cstring>

namespace nebula {
    namespace graphics {

    extern "C" int nlua_graphics_font(lua_State *L);
} // graphics
} // nebula
