#include "WrapPosition.hpp"

namespace nebula {
    namespace ecs {

    int w_positionIndex(lua_State *L) {
        ComponentProxy *proxy = (ComponentProxy*)luaL_checkudata(L, 1, "Position");
        Position *pos = (Position*) proxy->pointer;
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "x") == 0) {
            lua_pushnumber(L, pos->x);
        } else if (strcmp(key, "y") == 0) {
            lua_pushnumber(L, pos->y);
        } else {
            lua_pushnil(L);
        }

        return 1;
    }

    int w_positionNewIndex(lua_State *L) {
        ComponentProxy *proxy = (ComponentProxy*)luaL_checkudata(L, 1, "Position");
        Position *pos = (Position*) proxy->pointer;
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "x") == 0) {
            pos->x = (float)luaL_checknumber(L, 3);
        } else if (strcmp(key, "y") == 0) {
            pos->y = (float)luaL_checknumber(L, 3);
        } else {
            luaL_error(L, "Invalid field: Position.%s", key);
        }

        return 0;
    }

    static int w_positionToString(lua_State* L) {
        ComponentProxy *proxy = (ComponentProxy*)luaL_checkudata(L, 1, "Position");
        Position *pos = (Position*) proxy->pointer;
        lua_pushfstring(L, "Position(%f, %f)", pos->x, pos->y);
        return 1;
    }

    static int w_compName(lua_State *L) {
        lua_pushstring(L, "Position");
        return 1;
    }

    static int w_compId(lua_State *L) {
        lua_pushinteger(L, 1);
        return 1;
    }

    const luaL_Reg w_positionFuncs[] = {
        {"__index", w_positionIndex},
        {"__newindex", w_positionNewIndex},
        {"__tostring", w_positionToString},
        {0, 0}
    };

    const luaL_Reg w_positionFields[] = {
        {"__compName", w_compName},
        {"__compId", w_compId},
        {0, 0}
    };

    extern "C" int nlua_ecs_position(lua_State *L) {
        WrapType wrapPosition;
        wrapPosition.name = "Position";
        wrapPosition.funcs = w_positionFuncs;
        wrapPosition.fields = w_positionFields;

        return registerType(L, wrapPosition);
    }
} // ecs
} // nebula
