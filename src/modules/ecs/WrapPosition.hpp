#pragma once

#include "../common/WrapType.hpp"
#include "../common/LuaBidings.hpp"
#include "RenderComponents.hpp"

#include <cstring>

namespace nebula {
    namespace ecs {
    
    static int positionConstructor(lua_State *L, const bool emptyConstructor) {
        Position *pos = (Position*)lua_newuserdata(L, sizeof(Position));
        pos->x = 0.0f;
        pos->y = 0.0f;
        if (!emptyConstructor) {
            lua_pushnil(L); // first key
            while (lua_next(L, 2) != 0) {
                const char *keyName = lua_tostring(L, -2);

                if (strcmp(keyName, "x") == 0) {
                    pos->x = (float)luaL_checknumber(L, -1);
                } else if (strcmp(keyName, "y") == 0) {
                    pos->y = (float)luaL_checknumber(L, -1);
                } else {
                    luaL_error(L, "Invalid field: Position.%s", keyName);
                }

                lua_pop(L, 1); // pops value
            }
        }
        luaL_getmetatable(L, "Position");
        lua_setmetatable(L, -2);

        return 1;
    };

    extern "C" int nlua_ecs_position(lua_State *L);
} // ecs
} // nebula
