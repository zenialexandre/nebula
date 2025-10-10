#include "NebulaSetup.hpp"

extern "C" {
    extern int nlua_graphics(lua_State* L);
    extern int nlua_ecs(lua_State *L);
    extern int nlua_time(lua_State *L);
    extern int nlua_nebula_boot(lua_State *L);
    extern int nlua_nebula_baseScreen(lua_State *L);
    extern int nlua_window(lua_State *L);
    extern int nlua_event(lua_State *L);
}

static const char bootLua[] =
#include "boot.lua"
;

static const char baseScreenLua[] =
#include "baseScreen.lua"
;


static const luaL_Reg modules[] = {
    // modules
    {"nebula.window", nlua_window},
    {"nebula.graphics", nlua_graphics},
    {"nebula.ecs", nlua_ecs},
    {"nebula.time", nlua_time},
    {"nebula.event", nlua_event},
    // lua files
    {"nebula.boot", nlua_nebula_boot},
    {"nebula.baseScreen", nlua_nebula_baseScreen},
    {0, 0}
};

static int packagePreload(lua_State *L, lua_CFunction func, const char *packName) {
    // standard lua table "package"
    lua_getglobal(L, "package"); // places table at the top of stack
    lua_getfield(L, -1, "preload"); // retrieves the "preload" field from the table at the top of stack (-1)
    lua_pushcfunction(L, func);
    lua_setfield(L, -2, packName); // saves func on package at packName (key)
    lua_pop(L, 2); // pops 2 elements from the stack
    return 0;
}

int eensureGlobal(lua_State *L, const char *name) {
    lua_getglobal(L, name);
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setglobal(L, name);
    }
    return 1;
}

int nlua_nebula(lua_State *L) {
    for(int i = 0; modules[i].name != nullptr; i++) {
        packagePreload(L, modules[i].func, modules[i].name);
    }

    eensureGlobal(L, "nebula");

    return 1;
}

int nlua_nebula_boot(lua_State *L) {
    if(luaL_loadbuffer(L, bootLua, sizeof(bootLua), "boot nebula") == LUA_OK) {
        lua_call(L, 0, 1);
    }
    return 1;
}

int nlua_nebula_baseScreen(lua_State *L) {
    if(luaL_loadbuffer(L, baseScreenLua, sizeof(baseScreenLua), "base screen nebula") == LUA_OK) {
        lua_call(L, 0, 1);
    }
    return 1;
}