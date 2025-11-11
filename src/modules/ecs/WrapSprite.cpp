#include "WrapSprite.hpp"

namespace nebula {
    namespace ecs {

    int w_spriteIndex(lua_State *L) {
        ComponentProxy *proxy = (ComponentProxy*)luaL_checkudata(L, 1, "Sprite");
        Sprite *sprite = (Sprite*) proxy->pointer;
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "texture") == 0) {
            pushUserData<graphics::Texture>(L, sprite->texture, "Texture");
        } else {
            lua_pushnil(L);
        }

        return 1;
    }

    int w_spriteNewIndex(lua_State *L) {
        ComponentProxy *proxy = (ComponentProxy*)luaL_checkudata(L, 1, "Sprite");
        Sprite *sprite = (Sprite*) proxy->pointer;
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "texture") == 0) {
            if (!checkUserData<graphics::Texture>(L, 3)) {
                luaL_error(L, "Invalid Texture.");
            }
            ObjectProxy *proxy = (ObjectProxy*)luaL_checkudata(L, 3, "Texture");
            sprite->texture = (graphics::Texture*)proxy->pointer;
        } else {
            luaL_error(L, "Invalid field: Sprite.%s", key);
        }

        return 0;
    }

    static int w_spriteToString(lua_State* L) {
        ComponentProxy *proxy = (ComponentProxy*)luaL_checkudata(L, 1, "Sprite");
        Sprite *sprite = (Sprite*) proxy->pointer;
        lua_pushfstring(L, "Sprite");
        return 1;
    }

    static int w_compName(lua_State *L) {
        lua_pushstring(L, "Sprite");
        return 1;
    }

    static int w_compId(lua_State *L) {
        lua_pushinteger(L, 4);
        return 1;
    }

    const luaL_Reg w_spriteFuncs[] = {
        {"__index", w_spriteIndex},
        {"__newindex", w_spriteNewIndex},
        {"__tostring", w_spriteToString},
        {0, 0}
    };

    const luaL_Reg w_spriteFields[] = {
        {"__compName", w_compName},
        {"__compId", w_compId},
        {0, 0}
    };

    extern "C" int nlua_ecs_sprite(lua_State *L) {
        WrapType wrapSprite;
        wrapSprite.name = "Sprite";
        wrapSprite.funcs = w_spriteFuncs;
        wrapSprite.fields = w_spriteFields;

        return registerType(L, wrapSprite);
    }
} // ecs
} // nebula
