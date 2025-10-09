#include <iostream>

#include <Scripts/NebulaSetup.hpp>
#include <Data/File.hpp>

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

//static inline bool removeSubstr(std::string &full, const std::string &substring) {
//    if (substring.size() > full.size()) {
//        return false;
//    }
//
//    size_t pos = full.find(substring);
//
//    if (pos == std::string::npos) {
//        return false;
//    }
//
//    full.erase(pos, substring.length());
//    return true;
//}


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

        if (gamePath.size() != 0) {
            gamePath = nebula::data::File::getRelativePath(nebulaExePath, gamePath);
            gamePath.append("\\main.lua");
        } else {
            gamePath = "main.lua";
        }

        std::string fullPath = nebulaExePath;
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