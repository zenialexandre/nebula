#pragma once

#include "../common/WrapType.hpp"
#include "../common/LuaBidings.hpp"
#include "Components.hpp"

#include <cstring>

namespace nebula {
    namespace ecs {
    
    static int rotationConstructor(lua_State *L, const bool emptyConstructor) {
        Rotation *rotation = new Rotation();
        ComponentProxy *proxy = (ComponentProxy*)lua_newuserdata(L, sizeof(ComponentProxy));
        proxy->pointer = rotation;
        rotation->value = 0.0f;
        if (!emptyConstructor) {
            lua_pushnil(L); // first key
            while (lua_next(L, 2) != 0) {
                const char *keyName = lua_tostring(L, -2);

                if (strcmp(keyName, "value") == 0) {
                    rotation->value = (float)luaL_checknumber(L, -1);
                } else {
                    luaL_error(L, "Invalid field: Rotation.%s", keyName);
                }

                lua_pop(L, 1); // pops value
            }
        }
        luaL_getmetatable(L, "Rotation");
        lua_setmetatable(L, -2);

        return 1;
    };

    extern "C" int nlua_ecs_rotation(lua_State *L);
} // ecs
} // nebula
