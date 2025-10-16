#include "WrapKeyboard.hpp"

namespace nebula {

#define keyboard() (ModuleRegistry::getInstance<keyboard::Keyboard>(KEYBOARD))

    namespace keyboard {

int w_isKeyPressed(lua_State *L) {
    if (lua_gettop(L) != 1 || !luaL_checkstring(L, 1)) {
        luaL_error(L, "Invalid key!");
    }
    const char* keyName = lua_tostring(L, 1);
    const bool value = keyboard()->isKeyPressed(keyName);
    lua_pushboolean(L, value);
    return 1;
}

int w_isKeyReleased(lua_State *L) {
    if (lua_gettop(L) != 1 || !luaL_checkstring(L, 1)) {
        luaL_error(L, "Invalid key!");
    }
    const char* keyName = lua_tostring(L, 1);
    const bool value = keyboard()->isKeyReleased(keyName);
    lua_pushboolean(L, value);
    return 1;
}

int w_resetKeysReleased(lua_State *L) {
    keyboard()->resetKeysReleased();
    return 0;
}

static const luaL_Reg functions[] = {
    {"isKeyPressed", w_isKeyPressed},
    {"isKeyReleased", w_isKeyReleased},
    {"_resetKeysReleased", w_resetKeysReleased},
    {0, 0}
};

extern "C" int nlua_keyboard(lua_State *L) {
    Keyboard *instance = keyboard();

    WrapModule wModule;
    wModule.module = instance;
    wModule.funcs = functions;
    wModule.types = nullptr;

    return registerModule(L, wModule);
}

} // keyboard
} // nebula
