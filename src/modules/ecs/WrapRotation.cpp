#include "WrapRotation.hpp"

namespace nebula {
    namespace ecs {

    int w_rotationIndex(lua_State *L) {
        Rotation *rotation = (Rotation*)luaL_checkudata(L, 1, "Rotation");
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "value") == 0) {
            lua_pushnumber(L, rotation->value);
        } else {
            lua_pushnil(L);
        }

        return 1;
    }

    int w_rotationNewIndex(lua_State *L) {
        Rotation *rotation = (Rotation*)luaL_checkudata(L, 1, "Rotation");
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "value") == 0) {
            rotation->value = (float)luaL_checknumber(L, 3);
        } else {
            luaL_error(L, "Invalid field: %s", key);
        }

        return 0;
    }

    static int w_rotationToString(lua_State* L) {
        Rotation* rotation = (Rotation*)luaL_checkudata(L, 1, "Rotation");
        lua_pushfstring(L, "Rotation(%f)", rotation->value);
        return 1;
    }

    static int w_compName(lua_State *L) {
        lua_pushstring(L, "Rotation");
        return 1;
    }

    static int w_compId(lua_State *L) {
        lua_pushinteger(L, 7);
        return 1;
    }

    const luaL_Reg w_rotationFuncs[] = {
        {"__index", w_rotationIndex},
        {"__newindex", w_rotationNewIndex},
        {"__tostring", w_rotationToString},
        {0, 0}
    };

    const luaL_Reg w_rotationFields[] = {
        {"__compName", w_compName},
        {"__compId", w_compId},
        {0, 0}
    };

    extern "C" int nlua_ecs_rotation(lua_State *L) {
        WrapType wrapRotation;
        wrapRotation.name = "Rotation";
        wrapRotation.funcs = w_rotationFuncs;
        wrapRotation.fields = w_rotationFields;

        return registerType(L, wrapRotation);
    }
} // ecs
} // nebula
