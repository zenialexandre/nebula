#include "WrapWorld.hpp"
#include <iostream>

namespace nebula {

#define ecs() (ModuleRegistry::getInstance<ecs::World>(ECS))

	namespace ecs {
    
    struct LuaTableRef {
        int luaRefBaseTable = LUA_NOREF;
    };

    //struct LuaComponentMetadata {
    //    const char *name;
    //    const int numFields;
    //    int luaRefBaseTable = LUA_NOREF;
    //};

    // For each Lua registered component, we will create
    // an entity to store the component metadata
    //static std::unordered_map<ComponentId, EntityId> luaComponentEntityMap;

    //static int registerComponent(lua_State *L, const char *name, const int tableIdx) {
    //    if (ecs()->componentExists(name) != 0) {
    //        luaL_error(L, "You already registered a component with this name");
    //    }
    //    ComponentId compId = ecs()->registerComponent(name);
    //    int fieldCount = getNumOfTableFields(L, tableIdx);
    //    // duplicate the base table to store as reference
    //    lua_pushvalue(L, tableIdx);
    //    LuaComponentMetadata cMetadata = LuaComponentMetadata{
    //        name,
    //        fieldCount,
    //        luaL_ref(L, LUA_REGISTRYINDEX)
    //    };
    //    EntityId compEntId = ecs()->spawn();
    //    ecs()->addComponent(compEntId, cMetadata);
    //    luaComponentEntityMap.insert({compId, compEntId});
    //    return 0;
    //}

    static int componentConstructor(lua_State *L) {
        // create a table if there was no argTable
        int argsCount = lua_gettop(L);

        if (argsCount == 0) {
            luaL_error(L, "An error occurred while instantiating a component. Use 'Component:new()' instead of 'Component.new()'.");
        }

        if (argsCount == 1) {
            lua_newtable(L);
        }

        if (argsCount > 2) {
            luaL_error(L, "An error occurred while instantiating a component. Use 'Component:new()', 'Component:new(table)', 'Component()' or 'Component(table)'.");
        }

        if(!lua_getmetatable(L, 1)) {
            luaL_error(L, "An error occurred while instantiating a component. Use 'Component:new()' instead of 'Component.new()'.");
        }

        lua_getfield(L, -1, "__compId");
        ComponentId componentId = lua_tointeger(L, -1);
        lua_getfield(L, -2, "__compName");
        const char* componentName = lua_tostring(L, -1);
        lua_getfield(L, -3, "__fieldCount");
        const int baseFieldCount = lua_tointeger(L, -1);
        lua_pop(L, 3);

        if (baseFieldCount > 0) {
            lua_getfield(L, -1, "__prototype"); // base table

            // merge argTable with __prototype
            // if a (key, value) pair is missing, get from __prototype
            lua_pushnil(L); // first key
            while (lua_next(L, -2) != 0) {
                const char *keyName = lua_tostring(L, -2);
                lua_getfield(L, 2, keyName);

                // the key was not passed in func args, so use the value in "__prototype"
                if (lua_isnil(L, -1) && !lua_iscfunction(L, -2)) {
                    // ..., key, value, argTable[keyname]
                    lua_pop(L, 1);
                    // ..., key, value
                    lua_pushvalue(L, -1);
                    // ..., key, value, value
                    lua_setfield(L, 2, keyName);
                    // ..., key, value
                } else {
                    // ..., key, value, argTable[keyname]
                    lua_pop(L, 1);
                    // ..., key, value
                }

                lua_pop(L, 1); // pops value
            }
            lua_pop(L, 2); // pops __prototype and metatable
        } else {
            lua_pop(L, 1); // pops metatable
        }

        int argTableFieldCount = getNumOfTableFields(L, 2);

        if (argTableFieldCount != baseFieldCount) {
            std::cout << "argTableFieldCount: " << argTableFieldCount << " baseFieldCount: " << baseFieldCount << std::endl;
            lua_pushstring(L, componentName);
            luaL_error(
                L, 
                "An error occurred while instantiating the component %s. Check if the constructor matches the component registered.",
                lua_tostring(L, -1)
            );
        }

        lua_newtable(L);
        lua_pushinteger(L, componentId);
        lua_setfield(L, -2, "__compId");
        lua_pushstring(L, componentName);
        lua_setfield(L, -2, "__compName");
        lua_setmetatable(L, -2);
        return 1;
    }

    static int addLuaComponent(lua_State *L, const EntityId entId, const int cTabIdx) {
        if (!lua_istable(L, cTabIdx)) {
            luaL_error(L, "An error occurred while adding a Component. Check if the parameter is a registered Component.");
        }

        if(!lua_getmetatable(L, cTabIdx)) {
            luaL_error(L, "An error occurred while adding a Component. Check if the parameter is a registered Component.");
        }
        // ..., metatable
        lua_getfield(L, -1, "__compId");
        if (!lua_isinteger(L, -1)) {
            luaL_error(L, "An error occurred while adding a Component. Check if the parameter is a registered Component.");
        }
        ComponentId componentId = lua_tointeger(L, -1);

        lua_getfield(L, -2, "__compName");
        if (!lua_isstring(L, -1)) {
            luaL_error(L, "An error occurred while adding a Component. Check if the parameter is a registered Component.");
        }
        const char* componentName = lua_tostring(L, -1);
        
        // ..., metatable, __compId, __compName
        lua_pop(L, 3); // pops metatable, __compId, __compName

        ComponentId ecsCompId = ecs()->componentExists(componentName);

        if (ecsCompId != componentId) {
            luaL_error(L, "The Component does not match the ECS Registry. Check if the parameter is a registered Component.");
        }

        lua_pushvalue(L, cTabIdx); // pushes the table to create a ref
        ecs()->addComponentSafe(entId, ecsCompId, LuaTableRef{luaL_ref(L, LUA_REGISTRYINDEX)});

        return 0;
    }

    int w_spawn(lua_State *L) {
        lua_pushnumber(L, ecs()->spawn());
        return 1;
    }

    int w_print(lua_State *L) {
        ecs()->print();
        return 0;
    }

    int w_component(lua_State *L) {
        const char* compName = luaL_checkstring(L, 1);
        luaL_checktype(L, 2, LUA_TTABLE);

        if (ecs()->componentExists(compName) != 0) {
            luaL_error(L, "There already exists a component called '", compName, "'.");
        }

        ComponentId compId = ecs()->registerComponent(compName);

        int fieldCount = getNumOfTableFields(L, 2);

        // metatable
        lua_newtable(L);
        lua_pushcfunction(L, componentConstructor);
        lua_setfield(L, -2, "__call");
        lua_pushvalue(L, 2);
        lua_setfield(L, -2, "__prototype");
        lua_pushinteger(L, compId);
        lua_setfield(L, -2, "__compId");
        lua_pushstring(L, compName);
        lua_setfield(L, -2, "__compName");
        lua_pushinteger(L, fieldCount);
        lua_setfield(L, -2, "__fieldCount");
        lua_setmetatable(L, -2);

        lua_pushcfunction(L, componentConstructor);
        lua_setfield(L, 2, "new");
        return 1;
    }

    int w_addComponent(lua_State *L) {
        if (!lua_isinteger(L, 1)) {
            luaL_error(L, "Not a valid EntityID.");
        }

        int entId = lua_tointeger(L, 1);

        if (entId < 0) {
            luaL_error(L, "Not a valid EntityID.");
        }

        if (!ecs()->exists(entId)) {
            luaL_error(L, "Not a valid EntityID.");
        }

        const int numArgs = lua_gettop(L);

        for (int i = 2; i <= numArgs; i ++) {
            addLuaComponent(L, entId, i);
        }

        return 0;
    }

    static const luaL_Reg functions[] = {
        {"spawn", w_spawn},
        {"print", w_print},
        {"component", w_component},
        {"addComponent", w_addComponent},
        {0, 0}
    };

	extern "C" int nlua_ecs(lua_State *L) {
        World *ecs = ecs();

        WrapModule wModule;
        wModule.module = ecs;
        wModule.funcs = functions;

        return registerModule(L, wModule);
    }
} // ecs
} // nebula
