#include "WrapTime.hpp"

namespace nebula {

#define time() (ModuleRegistry::getInstance<time::Time>(TIME))

    namespace time {

int w_now(lua_State *L) {
    lua_pushnumber(L, time()->now());
    return 1;
}

int w_tick(lua_State *L) {
    lua_pushnumber(L, time()->tick());
    return 1;
}

int w_getDeltaTime(lua_State *L) {
    lua_pushnumber(L, time()->getDeltaTime());
    return 1;
}

int w_getFPS(lua_State *L) {
    lua_pushinteger(L, time()->getFPS());
    return 1;
}

int w_destructor(lua_State *L) {
    Time* obj = *(Time**)luaL_checkudata(L, 1, time()->getName());
    delete obj;
    return 0;
}

static const luaL_Reg functions[] = {
    {"now", w_now},
    {"tick", w_tick},
    {"getDeltaTime", w_getDeltaTime},
    {"getFPS", w_getFPS},
    {0, 0}
};

extern "C" int nlua_time(lua_State *L) {
    Time *time = time();

    WrapModule wModule;
    wModule.module = time;
    wModule.funcs = functions;
    wModule.types = nullptr;

    return registerModule(L, wModule);
}

} // time
} // nebula
