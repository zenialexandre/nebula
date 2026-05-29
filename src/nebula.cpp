#include <iostream>
#include <SDL3/SDL_main.h>

#include "scripts/NebulaSetup.hpp"
#include "data/File.hpp"

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

enum RunAction {
    RUN,
    QUIT
};

static int nlua_packagePreload(lua_State *L, lua_CFunction func, const char *packName) {
    // standard lua table "package"
    lua_getglobal(L, "package"); // places table at the top of stack
    lua_getfield(L, -1, "preload"); // retrieves the "preload" field from the table at the top of stack (-1)
    lua_pushcfunction(L, func);
    lua_setfield(L, -2, packName); // saves func on package at packName (key)
    lua_pop(L, 2); // pops 2 elements from the stack
    return 0;
}

static inline bool endsWith(const std::string &full, const std::string &ending) {
    if (full.size() < ending.size()) {
        return false;
    }

    return full.compare(full.size() - ending.size(), ending.size(), ending) == 0;
}


static RunAction runNebula(int argc, char **argv, int &mainReturn) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    nlua_packagePreload(L, nlua_nebula, "nebula");

    if(argc > 0) {
        // new table for pushing args
        lua_newtable(L);

        std::string nebulaExePath;
        std::string gamePath;
        for (int i = 0; i < argc; ++i) {
            if (nebula::data::File::isValidPath(argv[i])) {
                if (endsWith(argv[i], "nebula.exe")) {
                    lua_pushstring(L, argv[i]);
                    lua_setfield(L, -2, "_exePath");
                    nebulaExePath = argv[i];
                    nebulaExePath.erase(nebulaExePath.size() - std::string("nebula.exe").size());
                } else {
                    gamePath = argv[i];
                }
            }
        }

        //nebula::data::File::setCurrentPath(nebulaExePath);

        if (gamePath.size() != 0) {
            gamePath = nebula::data::File::setRelativePath(nebulaExePath, gamePath);

            std::replace(gamePath.begin(), gamePath.end(), '\\', '/');

            if (!gamePath.empty() && gamePath.back() != '/') {
                gamePath.append("/");
            }
            gamePath.append("main.lua");
        } else {
            gamePath = "main.lua";
        }

        std::string fullPath = nebulaExePath;
        std::replace(fullPath.begin(), fullPath.end(), '\\', '/');
        if (!fullPath.empty() && fullPath.back() != '/') {
            fullPath.append("/");
        }
        fullPath.append(gamePath);

        if (nebula::data::File::isValidPath(fullPath)) {
            lua_pushstring(L, gamePath.c_str());
            lua_setfield(L, -2, "_gamePath");
        }

        lua_setglobal(L, "_nebulaArgs");
    }

    lua_getglobal(L, "require");
    lua_pushstring(L, "nebula");
    lua_call(L, 1, 1);

    lua_pop(L, 1);

    lua_getglobal(L, "require");
	lua_pushstring(L, "nebula.boot");
	lua_call(L, 1, 1);

    lua_newthread(L);
    lua_pushvalue(L, -2);

    const int count = lua_gettop(L);
    int nresults;

    while(lua_resume(L, nullptr, 0, &nresults) == LUA_YIELD) {
        lua_pop(L, nresults);
    }

    if (lua_isnumber(L, count)) {
        mainReturn = lua_tonumber(L, count);
    }

    lua_close(L);

    return QUIT;
}

int main(int argc, char **argv) {
    int mainReturn = 0;

    nebula::setup();

    RunAction action = RUN;

    do {
        action = runNebula(argc, argv, mainReturn);
    } while (action != QUIT);

    SDL_Quit();
    return mainReturn;
}

// int main() {
//     bool run = true;

//     nebula::setup();

//     nebula::graphics::Graphics *graphics = nebula::ModuleRegistry::getInstance<nebula::graphics::Graphics>(nebula::GRAPHICS);
//     nebula::ecs::World *ecs = nebula::ModuleRegistry::getInstance<nebula::ecs::World>(nebula::ECS);
//     nebula::window::Window *window = nebula::ModuleRegistry::getInstance<nebula::window::Window>(nebula::WINDOW);
//     nebula::time::Time *time = nebula::ModuleRegistry::getInstance<nebula::time::Time>(nebula::TIME);
//     nebula::audio::Audio *audio = nebula::ModuleRegistry::getInstance<nebula::audio::Audio>(nebula::AUDIO);

//     auto ent1 = ecs->spawn();
//     auto ent2 = ecs->spawn();

//     std::cout << "1" << std::endl;
//     auto music = audio->newSource("resources/cyberpunk-music.wav");
//     auto aFont = graphics->newFont("documentation/examples/pong-2/resources/fonts/MaruMonica.ttf", 200);

//     std::cout << "2" << std::endl;
//     audio->play(music);
//     std::cout << "3" << std::endl;

//     ecs->addComponent(ent1, Quad{100.0f, 100.0f});
//     ecs->addComponent(ent1, Position{10.0f, 10.0f});
//     ecs->addComponent(ent1, Scale{0.5f, 0.5f});

//     ecs->addComponent(ent2, Text{aFont, "TESTE"});
//     ecs->addComponent(ent2, Position{500.0f, 200.0f});
//     ecs->addComponent(ent2, Color{0.0f, 1.0f, 0.0f, 1.0f});

//     graphics->setBackground(1.0f, 0.0f, 0.0f);

//     time->tick();

//     while (run) {
//         SDL_Event event{0};
//         while(SDL_PollEvent(&event)) {
//             switch (event.type) {
//                 case SDL_EVENT_QUIT: {
//                     run = false;
//                     break;
//                 }
//             }
//         }

//         auto dt = time->tick();

//         Position *e1pos = ecs->getComponent<Position>(ent1);
//         e1pos->x += 10.0f * dt;

//         Position *e2pos = ecs->getComponent<Position>(ent2);
//         e2pos->x -= 2.0f * dt;
//         e2pos->y -= 1.0f * dt;

//         graphics->beginScene(ecs);
//         graphics->draw(ent1);
//         graphics->draw(ent2);
//         graphics->endScene();
//         window->swapBuffers();
//     }

//     SDL_Quit();

//     return 0;
// }