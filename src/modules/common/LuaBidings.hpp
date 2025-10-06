#pragma once

#include "WrapModule.hpp"
#include "WrapType.hpp"
#include <iostream>

extern "C" {
    #include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

namespace nebula {

static int ensureGlobal(lua_State *L, const char *name) {
    lua_getglobal(L, name);
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setglobal(L, name);
    }
    return 1;
}

static int ensure(lua_State *L, int idx, const char *name) {
    if (idx < 0 && idx > LUA_REGISTRYINDEX) {
        idx += lua_gettop(L) + 1;
    }

    lua_getfield(L, idx, name);

    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setfield(L, idx, name);
    }

    return 1;
}

static int ensureTypeRegistry(lua_State *L) {
    lua_getfield(L, LUA_REGISTRYINDEX, "_nebulaTypes");
    if (!lua_istable(L, -1)) {
        lua_newtable(L);
		lua_replace(L, -2);
		lua_newtable(L);

		lua_pushliteral(L, "v");
		lua_setfield(L, -2, "__mode");

		lua_setmetatable(L, -2);

		lua_setfield(L, LUA_REGISTRYINDEX, "_nebulaTypes");
    } else {
        lua_pop(L, 1);
    }
    return 1;
}

static int ensureModuleRegistry(lua_State *L) {
    ensureGlobal(L, "nebula");
    ensure(L, -1, "_modules");

    lua_replace(L, -2);

    return 1;
}

static int getNumOfTableFields(lua_State *L, const int tableIdx) {
    int count = 0;

    if (!lua_istable(L, tableIdx)) {
        return count;
    }

    lua_pushnil(L);

    while (lua_next(L, tableIdx) != 0) {
        // key is at -2, value is at -1
        count++;
        // Pop the value, leaving the key for the next iteration
        lua_pop(L, 1);
    }

    return count;
}

static void registerFuncs(lua_State* L, const luaL_Reg* funcs) {
    if (funcs == nullptr) {
        return;
    }

    for (;funcs->name != nullptr; funcs++) {
        lua_pushcfunction(L, funcs->func);
        lua_setfield(L, -2, funcs->name);
    }
}

struct Pointer {
    nebula::Module *module;
};

static int w_gc(lua_State *L) {
    Pointer *t = (Pointer*)lua_touserdata(L, 1);
    delete t->module;
    return 0;
}

static int registerType(lua_State *L, WrapType &wType) {
    ensureTypeRegistry(L);

    luaL_newmetatable(L, wType.name);

    lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

    if (wType.funcs != nullptr) {
        registerFuncs(L, wType.funcs);
    }

    if (wType.fields != nullptr) {
        for (const luaL_Reg* fieldFunc = wType.fields; fieldFunc->name != nullptr; fieldFunc++) {
            fieldFunc->func(L);
            lua_setfield(L, -2, fieldFunc->name);
        }
    }

    lua_pop(L, 1);

    return 0;
}

static int registerModule(lua_State *L, WrapModule &wModule) {
    ensureModuleRegistry(L);

    Pointer *pointer = (Pointer*)lua_newuserdata(L, sizeof(Pointer));
    pointer->module = wModule.module;

    luaL_newmetatable(L, wModule.module->getName());
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    lua_pushcfunction(L, w_gc);
    lua_setfield(L, -2, "__gc");

    lua_setmetatable(L, -2);
	lua_setfield(L, -2, wModule.module->getName());
	lua_pop(L, 1);

    ensureGlobal(L, "nebula");

    lua_newtable(L);

    if (wModule.funcs != nullptr) {
        registerFuncs(L, wModule.funcs);
    }

    if (wModule.types != nullptr) {
        for (const lua_CFunction *type = wModule.types; *type != nullptr; type++) {
            (*type)(L); // dereference pointer and call it with lua_State
        }
    }

    lua_pushvalue(L, -1);
    lua_setfield(L, -3, wModule.module->getName());
    lua_remove(L, -2);

    return 1;
}
} // nebula
