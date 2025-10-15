#include "WrapGraphics.hpp"
#include "WrapTexture.hpp"

namespace nebula {

#define graphics() (ModuleRegistry::getInstance<graphics::Graphics>(GRAPHICS))
#define ecs() (ModuleRegistry::getInstance<ecs::World>(ECS))

    namespace graphics {

int w_draw(lua_State *L) {
    ecs::EntityId id = (ecs::EntityId) luaL_checknumber(L, 1);
    graphics()->draw(id);
    return 0;
}

int w_newTexture(lua_State *L) {
    if (lua_gettop(L) != 1 || !luaL_checkstring(L, 1)) {
        luaL_error(L, "This function should only receive the sprite path.");
    }

    const char* filePath = lua_tostring(L, 1);
    Texture *texture = graphics()->newTexture(filePath);
    if (texture == nullptr) {
        luaL_error(L, "Something went wrong when creating a sprite");
    }
    lua_pushlightuserdata(L, texture);
    luaL_getmetatable(L, "Texture");
    lua_setmetatable(L, -2);
    return 1;
}

int w_newFont(lua_State *L) {
    const int count = lua_gettop(L);
    if (count > 2 || count == 0 || !luaL_checkstring(L, 1)) {
        luaL_error(L, "This function should only receive the Font path and size (optional).");
    }

    const char* filePath = lua_tostring(L, 1);
    Font *font = nullptr;
    if (count == 1) {
        font = graphics()->newFont(filePath);
    }
    if (count == 2) {
        const int fontSize = luaL_checkinteger(L, 2);
        font = graphics()->newFont(filePath, fontSize);
    }

    if (font == nullptr) {
        luaL_error(L, "Something went wrong when creating a font");
    }
    lua_pushlightuserdata(L, font);
    luaL_getmetatable(L, "Font");
    lua_setmetatable(L, -2);
    return 1;
}

int w_setBackground(lua_State *L) {
    if (lua_gettop(L) == 3) {
        float r = (float)luaL_checknumber(L, 1);
        float g = (float)luaL_checknumber(L, 2);
        float b = (float)luaL_checknumber(L, 3);

        graphics()->setBackground(r, g, b);
    }
    if (lua_gettop(L) == 4) {
        float r = (float)luaL_checknumber(L, 1);
        float g = (float)luaL_checknumber(L, 2);
        float b = (float)luaL_checknumber(L, 3);
        float a = (float)luaL_checknumber(L, 4);

        graphics()->setBackground(r, g, b, a);
    }
    return 0;
}

int w_moveCamera(lua_State *L) {
    int count = lua_gettop(L);
    float x = 0, y = 0;
    if (count >= 1) {
        x = (float) lua_tonumber(L, 1);
    }
    if (count == 2) {
        y = (float) lua_tonumber(L, 2);
    }

    graphics()->moveCamera(x, y);
    return 0;
}

int w_moveCameraTo(lua_State *L) {
    float x = (float) lua_tonumber(L, 1);
    float y = (float) lua_tonumber(L, 2);

    graphics()->moveCameraTo(x, y);
    return 0;
}

int w_pointCameraTo(lua_State *L) {
    float x = (float) lua_tonumber(L, 1);
    float y = (float) lua_tonumber(L, 2);

    graphics()->pointCameraTo(x, y);
    return 0;
}

int w_beginScene(lua_State *L) {
    graphics()->beginScene(ecs());
    return 0;
}

int w_endScene(lua_State *L) {
    graphics()->endScene();
    return 0;
}

static const luaL_Reg functions[] = {
    {"draw", w_draw},
    {"newTexture", w_newTexture},
    {"newFont", w_newFont},
    {"setBackground", w_setBackground},
    {"moveCamera", w_moveCamera},
    {"moveCameraTo", w_moveCameraTo},
    {"pointCameraTo", w_pointCameraTo},
    {"_beginScene", w_beginScene},
    {"_endScene", w_endScene},
    {0, 0}
};

static const lua_CFunction types[] = {
    nlua_graphics_texture,
    0
};

extern "C" int nlua_graphics(lua_State *L) {
    Graphics *graphics = graphics();

    WrapModule wModule;
    wModule.module = graphics;
    wModule.funcs = functions;
    wModule.types = types;

    return registerModule(L, wModule);
}

} // graphics    
} // nebula
