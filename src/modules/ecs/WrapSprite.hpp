#pragma once

#include "../common/WrapType.hpp"
#include "../common/LuaBidings.hpp"
#include "../graphics/Texture.h"
#include "Components.hpp"

#include <cstring>

namespace nebula {
    namespace ecs {
    
    static int spriteConstructor(lua_State *L, const bool emptyConstructor) {
        Sprite *sprite = new Sprite();
        ComponentProxy *proxy = (ComponentProxy*)lua_newuserdata(L, sizeof(ComponentProxy));
        proxy->pointer = sprite;
        if (emptyConstructor) {
            luaL_error(L, "You cannot initialize a Sprite Component with no arguments.");
        }
        lua_pushnil(L); // first key
        while (lua_next(L, 2) != 0) {
            const char *keyName = lua_tostring(L, -2);
            if (strcmp(keyName, "texture") == 0) {
                if (!checkUserData<graphics::Texture>(L, -1)) {
                    luaL_error(L, "Invalid Texture.");
                }
                ObjectProxy *proxy = (ObjectProxy *)lua_touserdata(L, -1);
                sprite->texture = (graphics::Texture*)proxy->pointer;
            } else {
                luaL_error(L, "Invalid field: Sprite.%s", keyName);
            }
            lua_pop(L, 1); // pops value
        }

        luaL_getmetatable(L, "Sprite");
        lua_setmetatable(L, -2);

        return 1;
    };

    extern "C" int nlua_ecs_sprite(lua_State *L);
} // ecs
} // nebula
