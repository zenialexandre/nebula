#pragma once

#include "../common/WrapType.hpp"
#include "../common/LuaBidings.hpp"
#include "Components.hpp"

#include <cstring>

namespace nebula {
    namespace ecs {
    
    static int scaleConstructor(lua_State *L, const bool emptyConstructor) {
        Scale *scale = new Scale();
        ComponentProxy *proxy = (ComponentProxy*)lua_newuserdata(L, sizeof(ComponentProxy));
        proxy->pointer = scale;
        scale->x = 0.0f;
        scale->y = 0.0f;
        if (!emptyConstructor) {
            lua_pushnil(L); // first key
            while (lua_next(L, 2) != 0) {
                const char *keyName = lua_tostring(L, -2);

                if (strcmp(keyName, "x") == 0) {
                    scale->x = (float)luaL_checknumber(L, -1);
                } else if (strcmp(keyName, "y") == 0) {
                    scale->y = (float)luaL_checknumber(L, -1);
                } else {
                    luaL_error(L, "Invalid field: Scale.%s", keyName);
                }

                lua_pop(L, 1); // pops value
            }
        }
        luaL_getmetatable(L, "Scale");
        lua_setmetatable(L, -2);

        return 1;
    };

    extern "C" int nlua_ecs_scale(lua_State *L);
} // ecs
} // nebula
