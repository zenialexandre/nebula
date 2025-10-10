#pragma once

#include "Event.hpp"

#include "../common/WrapModule.hpp"
#include "../common/LuaBidings.hpp"

namespace nebula {
    namespace event {

extern "C" int nlua_event(lua_State *L);

} // event
} // nebula
