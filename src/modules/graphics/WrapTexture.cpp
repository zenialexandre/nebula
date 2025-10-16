#include "WrapTexture.hpp"

namespace nebula {
    namespace graphics {

    int w_textureIndex(lua_State *L) {
        Texture *texture = (Texture*)luaL_checkudata(L, 1, "Texture");
        const char *key = luaL_checkstring(L, 2);

        if (strcmp(key, "width") == 0) {
            lua_pushnumber(L, texture->width);
        } else if (strcmp(key, "height") == 0) {
            lua_pushnumber(L, texture->height);
        } else {
            lua_pushnil(L);
        }

        return 1;
    }

    int w_textureToString(lua_State *L) {
        Texture *texture = (Texture*)luaL_checkudata(L, 1, "Texture");
        lua_pushfstring(L, "Texture(id: %i, w: %f, h: %f)", texture->getId(), texture->width, texture->height);
        return 1;
    }

    const luaL_Reg w_textureFuncs[] = {
        {"__index", w_textureIndex},
        {"__tostring", w_textureToString},
        {0, 0}
    };

    extern "C" int nlua_graphics_texture(lua_State *L) {
        WrapType wrapTexture;
        wrapTexture.name = "Texture";
        wrapTexture.funcs = w_textureFuncs;
        wrapTexture.fields = nullptr;

        return registerType(L, wrapTexture);
    }
} // graphics
} // nebula
