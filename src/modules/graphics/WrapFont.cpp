#include "WrapFont.hpp"

namespace nebula {
    namespace graphics {

    int w_fontIndex(lua_State *L) {
        Font *font = (Font*)luaL_checkudata(L, 1, "Font");
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "lineHeight") == 0) {
            lua_pushnumber(L, font->getLineHeight());
        } else {
            lua_pushnil(L);
        }

        return 1;
    }

    int w_fontToString(lua_State *L) {
        Font *font = (Font*)luaL_checkudata(L, 1, "Font");
        lua_pushstring(L, "Font");
        return 1;
    }

    const luaL_Reg w_fontFuncs[] = {
        {"__index", w_fontIndex},
        {"__tostring", w_fontToString},
        {0, 0}
    };

    extern "C" int nlua_graphics_font(lua_State *L) {
        WrapType wrapFont;
        wrapFont.name = "Font";
        wrapFont.funcs = w_fontFuncs;
        wrapFont.fields = nullptr;

        return registerType(L, wrapFont);
    }
} // graphics
} // nebula
