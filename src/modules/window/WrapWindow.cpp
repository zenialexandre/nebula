#include "WrapWindow.hpp"

namespace nebula {

#define window() (ModuleRegistry::getInstance<window::Window>(WINDOW))
#define graphics() (ModuleRegistry::getInstance<graphics::Graphics>(GRAPHICS))

    namespace window {

int w_setWindow(lua_State *L) {
    if(lua_gettop(L) != 2) {
        luaL_error(L, "Invalid number of arguments.");
    }
    int width = luaL_checkinteger(L, 1);
    int height = luaL_checkinteger(L, 2);
    window()->setWindow(width, height);
    graphics()->setWindowSize(width, height);
    return 0;
}

int w_setTitle(lua_State *L) {
    std::string title = luaL_checkstring(L, 1);
    window()->setTitle(title);
    return 0;
}

int w_setIcon(lua_State *L) {
    std::string iconPath = luaL_checkstring(L, 1);
    window()->setIcon(iconPath);
    return 0;
}

int w_setFullscreen(lua_State *L) {
    luaL_checktype(L, 1, LUA_TBOOLEAN);
    bool fullscreen = lua_toboolean(L, 1);
    bool desktopMode = true;
    if (lua_gettop(L) == 2) {
        luaL_checktype(L, 2, LUA_TBOOLEAN);
        desktopMode = lua_toboolean(L, 2);
    }
    window()->setFullscreen(fullscreen, desktopMode);
    return 0;
}

int w_swapBuffers(lua_State *L) {
    if(lua_gettop(L) != 0) {
        luaL_error(L, "Invalid number of arguments.");
    }
    window()->swapBuffers();
    return 0;
}

static const luaL_Reg functions[] = {
    //{"setWindow", w_setWindow},
    {"setTitle", w_setTitle},
    {"setIcon", w_setIcon},
    {"setFullscreen", w_setFullscreen},
    {"swapBuffers", w_swapBuffers},
    {0, 0}
};

extern "C" int nlua_window(lua_State *L) {
    Window *window = window();

    WrapModule wModule;
    wModule.module = window;
    wModule.funcs = functions;
    wModule.types = nullptr;

    return registerModule(L, wModule);
}

} // window    
} // nebula
