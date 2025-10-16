#include "WrapCollisionBox.hpp"

namespace nebula {
    namespace ecs {

    int w_collisionBoxIndex(lua_State *L) {
        CollisionBox *collisionBox = (CollisionBox*)luaL_checkudata(L, 1, "CollisionBox");
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "width") == 0) {
            lua_pushnumber(L, collisionBox->width);
        } else if (strcmp(key, "height") == 0) {
            lua_pushnumber(L, collisionBox->height);
        } else if (strcmp(key, "x") == 0) {
            lua_pushnumber(L, collisionBox->x);
        } else if (strcmp(key, "y") == 0) {
            lua_pushnumber(L, collisionBox->y);
        } else {
            lua_pushnil(L);
        }

        return 1;
    }

    int w_collisionBoxNewIndex(lua_State *L) {
        CollisionBox *collisionBox = (CollisionBox*)luaL_checkudata(L, 1, "CollisionBox");
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "width") == 0) {
            collisionBox->width = (float)luaL_checknumber(L, 3);
        } else if (strcmp(key, "height") == 0) {
            collisionBox->height = (float)luaL_checknumber(L, 3);
        } else if (strcmp(key, "x") == 0) {
            collisionBox->x = (float)luaL_checknumber(L, 3);
        } else if (strcmp(key, "y") == 0) {
            collisionBox->y = (float)luaL_checknumber(L, 3);
        } else {
            luaL_error(L, "Invalid field: %s", key);
        }

        return 0;
    }

    static int w_collisionBoxToString(lua_State* L) {
        CollisionBox* collisionBox = (CollisionBox*)luaL_checkudata(L, 1, "CollisionBox");
        lua_pushfstring(L, "CollisionBox(w: %f, h: %f, x: %f, y: %f)", collisionBox->width, collisionBox->height, collisionBox->x, collisionBox->y);
        return 1;
    }

    static int w_compName(lua_State *L) {
        lua_pushstring(L, "CollisionBox");
        return 1;
    }

    static int w_compId(lua_State *L) {
        lua_pushinteger(L, 8);
        return 1;
    }

    const luaL_Reg w_collisionBoxFuncs[] = {
        {"__index", w_collisionBoxIndex},
        {"__newindex", w_collisionBoxNewIndex},
        {"__tostring", w_collisionBoxToString},
        {0, 0}
    };

    const luaL_Reg w_collisionBoxFields[] = {
        {"__compName", w_compName},
        {"__compId", w_compId},
        {0, 0}
    };

    extern "C" int nlua_ecs_collisionBox(lua_State *L) {
        WrapType wrapCollisionBox;
        wrapCollisionBox.name = "CollisionBox";
        wrapCollisionBox.funcs = w_collisionBoxFuncs;
        wrapCollisionBox.fields = w_collisionBoxFields;

        return registerType(L, wrapCollisionBox);
    }
} // ecs
} // nebula
