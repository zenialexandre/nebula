#pragma once

#include "Module.hpp"

extern "C" {
    #include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

namespace nebula {

struct WrapModule {
    Module *module;

    const luaL_Reg* funcs;
};

} // nebula
