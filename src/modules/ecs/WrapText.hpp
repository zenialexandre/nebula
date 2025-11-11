#pragma once

#include "../common/WrapType.hpp"
#include "../common/LuaBidings.hpp"
#include "../graphics/Font.hpp"
#include "Components.hpp"

#include <cstring>

namespace nebula {
    namespace ecs {
    
    static int textConstructor(lua_State *L, const bool emptyConstructor) {
        Text *text = new Text();
        ComponentProxy *proxy = (ComponentProxy*)lua_newuserdata(L, sizeof(ComponentProxy));
        proxy->pointer = text;
        new (&text->value) std::string(); // initializing text->value
        text->font = nullptr;
        if (emptyConstructor) {
            luaL_error(L, "You cannot initialize a Text Component with no arguments.");
        }
        lua_pushnil(L); // first key
        while (lua_next(L, 2) != 0) {
            const char *keyName = lua_tostring(L, -2);
            if (strcmp(keyName, "font") == 0) {
                if (!checkUserData<graphics::Font>(L, -1)) {
                    luaL_error(L, "Invalid Font.");
                }
                ObjectProxy *proxy = (ObjectProxy *)lua_touserdata(L, -1);
                text->font = (graphics::Font*)proxy->pointer;
            } else if (strcmp(keyName, "value") == 0) {
                text->value = luaL_checkstring(L, -1);
            } else {
                luaL_error(L, "Invalid field: Text.%s", keyName);
            }
            lua_pop(L, 1); // pops value
        }

        luaL_getmetatable(L, "Text");
        lua_setmetatable(L, -2);

        return 1;
    };

    extern "C" int nlua_ecs_text(lua_State *L);
} // ecs
} // nebula
