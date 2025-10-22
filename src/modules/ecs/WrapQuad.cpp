#include "WrapQuad.hpp"

namespace nebula {
    namespace ecs {

    int w_quadIndex(lua_State *L) {
        Quad *quad = (Quad*)luaL_checkudata(L, 1, "Quad");
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "width") == 0) {
            lua_pushnumber(L, quad->width);
        } else if (strcmp(key, "height") == 0) {
            lua_pushnumber(L, quad->height);
        } else {
            lua_pushnil(L);
        }

        return 1;
    }

    int w_quadNewIndex(lua_State *L) {
        Quad *quad = (Quad*)luaL_checkudata(L, 1, "Quad");
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "width") == 0) {
            quad->width = (float)luaL_checknumber(L, 3);
        } else if (strcmp(key, "height") == 0) {
            quad->height = (float)luaL_checknumber(L, 3);
        } else {
            luaL_error(L, "Invalid field: Quad.%s", key);
        }

        return 0;
    }

    static int w_quadToString(lua_State* L) {
        Quad* quad = (Quad*)luaL_checkudata(L, 1, "Quad");
        lua_pushfstring(L, "Quad(w: %f, h: %f)", quad->width, quad->height);
        return 1;
    }

    static int w_quadGc(lua_State *L) {
        Quad *color = (Quad*)luaL_checkudata(L, 1, "Quad");
        return 0;
    }

    static int w_compName(lua_State *L) {
        lua_pushstring(L, "Quad");
        return 1;
    }

    static int w_compId(lua_State *L) {
        lua_pushinteger(L, 3);
        return 1;
    }

    const luaL_Reg w_quadFuncs[] = {
        {"__index", w_quadIndex},
        {"__newindex", w_quadNewIndex},
        {"__tostring", w_quadToString},
        {"__gc", w_quadGc},
        {0, 0}
    };

    const luaL_Reg w_quadFields[] = {
        {"__compName", w_compName},
        {"__compId", w_compId},
        {0, 0}
    };

    extern "C" int nlua_ecs_quad(lua_State *L) {
        WrapType wrapQuad;
        wrapQuad.name = "Quad";
        wrapQuad.funcs = w_quadFuncs;
        wrapQuad.fields = w_quadFields;

        return registerType(L, wrapQuad);
    }
} // ecs
} // nebula
