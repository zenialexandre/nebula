#include "WrapColor.hpp"

namespace nebula {
    namespace ecs {

    int w_colorIndex(lua_State *L) {
        ComponentProxy *proxy = (ComponentProxy*)luaL_checkudata(L, 1, "Color");
        Color *color = (Color*) proxy->pointer;
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "r") == 0) {
            lua_pushnumber(L, color->r);
        } else if (strcmp(key, "g") == 0) {
            lua_pushnumber(L, color->g);
        } else if (strcmp(key, "b") == 0) {
            lua_pushnumber(L, color->b);
        } else if (strcmp(key, "a") == 0) {
            lua_pushnumber(L, color->a);
        } else {
            lua_pushnil(L);
        }

        return 1;
    }

    int w_colorNewIndex(lua_State *L) {
        ComponentProxy *proxy = (ComponentProxy*)luaL_checkudata(L, 1, "Color");
        Color *color = (Color*) proxy->pointer;
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "r") == 0) {
            color->r = (float)luaL_checknumber(L, 3);
        } else if (strcmp(key, "g") == 0) {
            color->g = (float)luaL_checknumber(L, 3);
        } else if (strcmp(key, "b") == 0) {
            color->b = (float)luaL_checknumber(L, 3);
        } else if (strcmp(key, "a") == 0) {
            color->a = (float)luaL_checknumber(L, 3);
        } else {
            luaL_error(L, "Invalid field: Color.%s", key);
        }

        return 0;
    }

    static int w_colorToString(lua_State* L) {
        ComponentProxy *proxy = (ComponentProxy*)luaL_checkudata(L, 1, "Color");
        Color *color = (Color*) proxy->pointer;
        lua_pushfstring(L, "Color(r: %f, g: %f, b: %f, a: %f)", color->r, color->g, color->b, color->a);
        return 1;
    }

    static int w_compName(lua_State *L) {
        lua_pushstring(L, "Color");
        return 1;
    }

    static int w_compId(lua_State *L) {
        lua_pushinteger(L, 6);
        return 1;
    }

    const luaL_Reg w_colorFuncs[] = {
        {"__index", w_colorIndex},
        {"__newindex", w_colorNewIndex},
        {"__tostring", w_colorToString},
        {0, 0}
    };

    const luaL_Reg w_colorFields[] = {
        {"__compName", w_compName},
        {"__compId", w_compId},
        {0, 0}
    };

    extern "C" int nlua_ecs_color(lua_State *L) {
        WrapType wrapColor;
        wrapColor.name = "Color";
        wrapColor.funcs = w_colorFuncs;
        wrapColor.fields = w_colorFields;

        return registerType(L, wrapColor);
    }
} // ecs
} // nebula
