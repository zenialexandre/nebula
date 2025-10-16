#include "WrapPhysics.hpp"

namespace nebula {

    #define physics() (ModuleRegistry::getInstance<physics::Physics>(PHYSICS))

    namespace physics {

int w_checkCollision(lua_State *L) {
    ecs::EntityId id1 = (ecs::EntityId) luaL_checknumber(L, 1);
    ecs::EntityId id2 = (ecs::EntityId) luaL_checknumber(L, 2);
    bool collision = physics()->checkCollision(id1, id2);
    lua_pushboolean(L, collision);
    return 1;
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