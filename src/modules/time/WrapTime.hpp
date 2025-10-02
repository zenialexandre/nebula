#pragma once

#include "Time.hpp"
#include "../common/WrapModule.hpp"
#include "../common/LuaBidings.hpp"

namespace nebula {
	namespace time {

	extern "C" int nlua_time(lua_State *L);
} // time
} // nebula
