#include <SDL3/SDL.h>
#include <iostream>

#include <Scripts/NebulaSetup.hpp>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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


static RunAction runNebula(int argc, char **argv, int &mainReturn) {
    // TODO args handling

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    nlua_packagePreload(L, nlua_nebula, "nebula");

    lua_getglobal(L, "require");
    lua_pushstring(L, "nebula");
    lua_call(L, 1, 1);

    lua_pop(L, 1);

    lua_getglobal(L, "require");
	lua_pushstring(L, "nebula.boot");
	lua_call(L, 1, 1);

    lua_close(L);

    return QUIT;
}

int main(int argc, char **argv) {
    int mainReturn = 0;

    nebula::setup();

    RunAction action = RUN;

    std::cout << "argc: " << argc << std::endl;

    for (int i = 0; i < argc; ++i) {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }

    do {
        action = runNebula(argc, argv, mainReturn);
    } while (action != QUIT);

    SDL_Quit();
    return mainReturn;
}