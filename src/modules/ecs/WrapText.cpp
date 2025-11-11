#include "WrapText.hpp"

namespace nebula {
    namespace ecs {

    int w_textIndex(lua_State *L) {
        ComponentProxy *proxy = (ComponentProxy*)luaL_checkudata(L, 1, "Text");
        Text *text = (Text*) proxy->pointer;
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "font") == 0) {
            pushUserData<graphics::Font>(L, text->font, "Font");
        } else if (strcmp(key, "value") == 0) {
            lua_pushstring(L, text->value.c_str());
        } else {
            lua_pushnil(L);
        }

        return 1;
    }

    int w_textNewIndex(lua_State *L) {
        ComponentProxy *proxy = (ComponentProxy*)luaL_checkudata(L, 1, "Text");
        Text *text = (Text*) proxy->pointer;
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "font") == 0) {
            if (!checkUserData<graphics::Font>(L, 3)) {
                luaL_error(L, "Invalid Font.");
            }
            ObjectProxy *proxy = (ObjectProxy*)luaL_checkudata(L, 3, "Font");
            text->font = (graphics::Font*)proxy->pointer;
        } else if (strcmp(key, "value") == 0) {
            std::string s = luaL_checkstring(L, 3);
            text->value = s;
        } else {
            luaL_error(L, "Invalid field: Text.%s", key);
        }

        return 0;
    }

    static int w_textToString(lua_State* L) {
        ComponentProxy *proxy = (ComponentProxy*)luaL_checkudata(L, 1, "Text");
        Text *text = (Text*) proxy->pointer;
        lua_pushfstring(L, "Text(value: %s)", text->value.c_str());
        return 1;
    }

    static int w_compName(lua_State *L) {
        lua_pushstring(L, "Text");
        return 1;
    }

    static int w_compId(lua_State *L) {
        lua_pushinteger(L, 5);
        return 1;
    }

    const luaL_Reg w_textFuncs[] = {
        {"__index", w_textIndex},
        {"__newindex", w_textNewIndex},
        {"__tostring", w_textToString},
        {0, 0}
    };

    const luaL_Reg w_textFields[] = {
        {"__compName", w_compName},
        {"__compId", w_compId},
        {0, 0}
    };

    extern "C" int nlua_ecs_text(lua_State *L) {
        WrapType wrapText;
        wrapText.name = "Text";
        wrapText.funcs = w_textFuncs;
        wrapText.fields = w_textFields;

        return registerType(L, wrapText);
    }
} // ecs
} // nebula
