#pragma once

#include "World.hpp"
#include "../common/WrapModule.hpp"
#include "../common/LuaBidings.hpp"

namespace nebula {
	namespace ecs {

	extern "C" int nlua_ecs(lua_State *L);
} // ecs
} // nebula
