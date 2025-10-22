#pragma once

#include "../common/WrapType.hpp"
#include "../common/LuaBidings.hpp"
#include "RenderComponents.hpp"

#include <cstring>

namespace nebula {
    namespace ecs {
    
    static int colorConstructor(lua_State *L, const bool emptyConstructor) {
        Color *color = (Color*)lua_newuserdata(L, sizeof(Color));
        color->r = 1.0f;
        color->g = 1.0f;
        color->b = 1.0f;
        color->a = 1.0f;
        if (!emptyConstructor) {
            lua_pushnil(L); // first key
            while (lua_next(L, 2) != 0) {
                const char *keyName = lua_tostring(L, -2);

                if (strcmp(keyName, "r") == 0) {
                    color->r = (float)luaL_checknumber(L, -1);
                } else if (strcmp(keyName, "g") == 0) {
                    color->g = (float)luaL_checknumber(L, -1);
                } else if (strcmp(keyName, "b") == 0) {
                    color->b = (float)luaL_checknumber(L, -1);
                } else if (strcmp(keyName, "a") == 0) {
                    color->a = (float)luaL_checknumber(L, -1);
                } else {
                    luaL_error(L, "Invalid field: Color.%s", keyName);
                }

                lua_pop(L, 1); // pops value
            }
        }
        luaL_getmetatable(L, "Color");
        lua_setmetatable(L, -2);

        return 1;
    };

    extern "C" int nlua_ecs_color(lua_State *L);
} // ecs
} // nebula
