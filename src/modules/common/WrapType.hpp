#pragma once

extern "C" {
    #include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

namespace nebula {

struct WrapType {
    const char *name;

    const luaL_Reg *funcs;
    const luaL_Reg *fields;
};

} // nebula