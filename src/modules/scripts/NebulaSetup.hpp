#pragma once

#include <Graphics/Graphics.h>
#include <Window/Window.h>
#include <Time/WrapTime.hpp>
#include <Ecs/WrapWorld.hpp>
#include <Event/WrapEvent.hpp>
#include <Keyboard/WrapKeyboard.hpp>
#include <Mouse/WrapMouse.hpp>
#include <Physics/WrapPhysics.hpp>

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>

    int nlua_nebula(lua_State *L);
}

namespace nebula {
    static bool setup() {
        ecs::World *world = new ecs::World();

        world->registerComponent<Position>("Position");
        world->registerComponent<Scale>("Scale");
        world->registerComponent<Quad>("Quad");
        world->registerComponent<Sprite>("Sprite");
        world->registerComponent<Text>("Text");
        world->registerComponent<Color>("Color");
        world->registerComponent<Rotation>("Rotation");
        world->registerComponent<CollisionBox>("CollisionBox");
        
        window::Window *window = new window::Window();
        window->createWindow();
        
        graphics::Graphics *graphics = new graphics::Graphics(window->getWidth(), window->getHeight());

        time::Time *time = new time::Time();
        event::Event *event = new event::Event();
        physics::Physics *physics = new physics::Physics(world);
        keyboard::Keyboard *keyboard = new keyboard::Keyboard();
        mouse::Mouse *mouse = new mouse::Mouse();

        if(!graphics->initialize()) {
            SDL_Log("%s", "ERROR INITIALIZING GRAPHICS");
            return false;
        }

        return true;
    }
} // nebula