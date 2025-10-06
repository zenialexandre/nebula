#pragma once

#include <Graphics/Graphics.h>
#include <Window/Window.h>
#include <Time/WrapTime.hpp>
#include <Ecs/WrapWorld.hpp>

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>

    int nlua_nebula(lua_State *L);
}

namespace nebula {
    static bool setup() {
        ecs::World *world = new ecs::World();

        world->registerComponent("Position");
        world->registerComponent("Scale");
        world->registerComponent("Quad");
        world->registerComponent("Sprite");
        
        window::Window *window = new window::Window();
        window->setWindow();
        
        graphics::Graphics *graphics = new graphics::Graphics(window->getWidth(), window->getHeight());

        time::Time *time = new time::Time();

        if(!graphics->initialize()) {
            SDL_Log("%s", "ERROR INITIALIZING GRAPHICS");
            return false;
        }

        return true;
    }
} // nebula