#pragma once

#include "../common/WrapType.hpp"
#include "../common/LuaBidings.hpp"
#include "RenderComponents.hpp"

#include <cstring>

namespace nebula {
    namespace ecs {
    
    static int collisionBoxConstructor(lua_State *L, const bool emptyConstructor) {
        CollisionBox *collisionBox = (CollisionBox*)lua_newuserdata(L, sizeof(CollisionBox));
        collisionBox->width = 0.0f;
        collisionBox->height = 0.0f;
        collisionBox->x = 0.0f;
        collisionBox->y = 0.0f;
        if (!emptyConstructor) {
            lua_pushnil(L); // first key
            while (lua_next(L, 2) != 0) {
                const char *keyName = lua_tostring(L, -2);

                if (strcmp(keyName, "width") == 0) {
                    collisionBox->width = (float)luaL_checknumber(L, -1);
                } else if (strcmp(keyName, "height") == 0) {
                    collisionBox->height = (float)luaL_checknumber(L, -1);
                } else if (strcmp(keyName, "x") == 0) {
                    collisionBox->x = (float)luaL_checknumber(L, -1);
                } else if (strcmp(keyName, "y") == 0) {
                    collisionBox->y = (float)luaL_checknumber(L, -1);
                } else {
                    luaL_error(L, "Invalid field: CollisionBox.%s", keyName);
                }

                lua_pop(L, 1); // pops value
            }
        }
        luaL_getmetatable(L, "CollisionBox");
        lua_setmetatable(L, -2);

        return 1;
    };

    extern "C" int nlua_ecs_collisionBox(lua_State *L);
} // ecs
} // nebula
