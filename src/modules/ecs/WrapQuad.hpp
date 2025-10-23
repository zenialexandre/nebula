#pragma once

#include "../common/WrapType.hpp"
#include "../common/LuaBidings.hpp"
#include "Components.hpp"

#include <cstring>

namespace nebula {
    namespace ecs {
    
    static int quadConstructor(lua_State *L, const bool emptyConstructor) {
        Quad *quad = new Quad();
        ComponentProxy *proxy = (ComponentProxy*)lua_newuserdata(L, sizeof(ComponentProxy));
        proxy->pointer = quad;
        quad->width = 0.0f;
        quad->height = 0.0f;
        if (!emptyConstructor) {
            lua_pushnil(L); // first key
            while (lua_next(L, 2) != 0) {
                const char *keyName = lua_tostring(L, -2);

                if (strcmp(keyName, "width") == 0) {
                    quad->width = (float)luaL_checknumber(L, -1);
                } else if (strcmp(keyName, "height") == 0) {
                    quad->height = (float)luaL_checknumber(L, -1);
                } else {
                    luaL_error(L, "Invalid field: Quad.%s", keyName);
                }

                lua_pop(L, 1); // pops value
            }
        }
        luaL_getmetatable(L, "Quad");
        lua_setmetatable(L, -2);

        return 1;
    };

    extern "C" int nlua_ecs_quad(lua_State *L);
} // ecs
} // nebula
