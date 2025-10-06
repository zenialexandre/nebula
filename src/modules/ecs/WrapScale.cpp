#include "WrapScale.hpp"

namespace nebula {
    namespace ecs {

    int w_scaleIndex(lua_State *L) {
        Scale *scale = (Scale*)luaL_checkudata(L, 1, "Scale");
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "x") == 0) {
            lua_pushnumber(L, scale->x);
        } else if (strcmp(key, "y") == 0) {
            lua_pushnumber(L, scale->y);
        } else {
            lua_pushnil(L);
        }

        return 1;
    }

    int w_scaleNewIndex(lua_State *L) {
        Scale *scale = (Scale*)luaL_checkudata(L, 1, "Scale");
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "x") == 0) {
            scale->x = (float)luaL_checknumber(L, 3);
        } else if (strcmp(key, "y") == 0) {
            scale->y = (float)luaL_checknumber(L, 3);
        } else {
            luaL_error(L, "Invalid field: %s", key);
        }

        return 0;
    }

    static int w_scaleToString(lua_State* L) {
        Scale* scale = (Scale*)luaL_checkudata(L, 1, "Scale");
        lua_pushfstring(L, "Scale(%f, %f)", scale->x, scale->y);
        return 1;
    }

    static int w_compName(lua_State *L) {
        lua_pushstring(L, "Scale");
        return 1;
    }

    static int w_compId(lua_State *L) {
        lua_pushinteger(L, 2);
        return 1;
    }

    const luaL_Reg w_scaleFuncs[] = {
        {"__index", w_scaleIndex},
        {"__newindex", w_scaleNewIndex},
        {"__tostring", w_scaleToString},
        {0, 0}
    };

    const luaL_Reg w_scaleFields[] = {
        {"__compName", w_compName},
        {"__compId", w_compId},
        {0, 0}
    };

    extern "C" int nlua_ecs_scale(lua_State *L) {
        WrapType wrapScale;
        wrapScale.name = "Scale";
        wrapScale.funcs = w_scaleFuncs;
        wrapScale.fields = w_scaleFields;

        return registerType(L, wrapScale);
    }
} // ecs
} // nebula
