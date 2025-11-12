#include "WrapPhysics.hpp"

namespace nebula {

    #define physics() (ModuleRegistry::getInstance<physics::Physics>(PHYSICS))

    namespace physics {

int w_checkCollision(lua_State *L) {
    int count = lua_gettop(L);
    if (count == 2) {
        ecs::EntityId id1 = (ecs::EntityId) luaL_checknumber(L, 1);
        ecs::EntityId id2 = (ecs::EntityId) luaL_checknumber(L, 2);
        bool collision = physics()->checkCollision(id1, id2);
        lua_pushboolean(L, collision);
        return 1;
    }
    if (count == 3) {
        float x = (float) luaL_checknumber(L, 1);
        float y = (float) luaL_checknumber(L, 2);
        ecs::EntityId entity = (ecs::EntityId) luaL_checknumber(L, 3);
        bool collision = physics()->checkCollision(x, y, entity);
        lua_pushboolean(L, collision);
        return 1;
    }
    return 0;
}

static const luaL_Reg functions[] = {
    {"checkCollision", w_checkCollision},
    {0, 0}
};

extern "C" int nlua_physics(lua_State *L) {
    Physics *physics = physics();

    WrapModule wModule;
    wModule.module = physics;
    wModule.funcs = functions;
    wModule.types = nullptr;

    return registerModule(L, wModule);
}

} // physics    
} // nebula