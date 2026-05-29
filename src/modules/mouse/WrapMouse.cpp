#include "WrapMouse.hpp"

namespace nebula {

#define mouse() (ModuleRegistry::getInstance<mouse::Mouse>(MOUSE))

    namespace mouse {

int w_getX(lua_State *L) {
    float x, y;
    mouse()->getPosition(x, y);
    lua_pushnumber(L, x);
    return 1;
}

int w_getY(lua_State *L) {
    float x, y;
    mouse()->getPosition(x, y);
    lua_pushnumber(L, y);
    return 1;
}

int w_getPosition(lua_State *L) {
    float x, y;
    mouse()->getPosition(x, y);
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    return 2;
}

int w_setX(lua_State *L) {
    float x, y;
    mouse()->getPosition(x, y);
    x = (float) luaL_checknumber(L, 1);
    mouse()->setPosition(x, y);
    return 0;
}

int w_setY(lua_State *L) {
    float x, y;
    mouse()->getPosition(x, y);
    y = (float) luaL_checknumber(L, 1);
    mouse()->setPosition(x, y);
    return 0;
}

int w_setPosition(lua_State *L) {
    float x, y;
    x = (float) luaL_checknumber(L, 1);
    y = (float) luaL_checknumber(L, 2);
    mouse()->setPosition(x, y);
    return 0;
}

int w_isPressed(lua_State *L) {
    const char* btnName = luaL_checkstring(L, 1);

    bool btnPressed = mouse()->isPressed(btnName);
    lua_pushboolean(L, btnPressed);
    return 1;
}

int w_isReleased(lua_State *L) {
    const char* btnName = luaL_checkstring(L, 1);

    bool btnReleased = mouse()->isReleased(btnName);
    lua_pushboolean(L, btnReleased);
    return 1;
}

int w_isGrabbed(lua_State *L) {
    bool grabbed = mouse()->isGrabbed();
    lua_pushboolean(L, grabbed);
    return 1;
}

int w_setGrabbed(lua_State *L) {
    luaL_checktype(L, 1, LUA_TBOOLEAN);
    bool grabbed = lua_toboolean(L, 1);
    mouse()->setGrabbed(grabbed);
    return 0;
}

static const luaL_Reg functions[] = {
    {"getX", w_getX},
    {"getY", w_getY},
    {"getPosition", w_getPosition},
    {"setX", w_setX},
    {"setY", w_setY},
    {"setPosition", w_setPosition},
    {"isPressed", w_isPressed},
    {"isReleased", w_isReleased},
    {"isGrabbed", w_isGrabbed},
    {"setGrabbed", w_setGrabbed},
    {0, 0}
};

extern "C" int nlua_mouse(lua_State *L) {
    Mouse *instance = mouse();

    WrapModule wModule;
    wModule.module = instance;
    wModule.funcs = functions;
    wModule.types = nullptr;

    return registerModule(L, wModule);
}

} // mouse
} // nebula
