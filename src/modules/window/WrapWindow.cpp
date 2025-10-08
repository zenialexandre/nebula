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

int w_swapBuffers(lua_State *L) {
    if(lua_gettop(L) != 0) {
        luaL_error(L, "Invalid number of arguments.");
    }
    window()->swapBuffers();
    return 0;
}

static const luaL_Reg functions[] = {
    {"setWindow", w_setWindow},
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
