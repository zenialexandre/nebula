#include "WrapWorld.hpp"
#include "WrapPosition.hpp"
#include "WrapScale.hpp"
#include "WrapQuad.hpp"
#include "WrapSprite.hpp"
#include "WrapText.hpp"
#include "WrapColor.hpp"
#include "WrapRotation.hpp"

#include <iostream>
namespace nebula {

#define ecs() (ModuleRegistry::getInstance<ecs::World>(ECS))

	namespace ecs {

    enum ComponentValidationMethod {
        DEFINITION,
        INSTANCE
    };

    enum ComponentType {
        NEBULA_DEFINED,
        USER_DEFINED
    };

    // explicitly showing the integer values, even though it is not needed
    enum NebulaComponents {
        NONE = 0,
        POSITION = 1,
        SCALE = 2,
        QUAD = 3,
        SPRITE = 4,
        TEXT = 5,
        COLOR = 6,
        ROTATION = 7
    };

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

    static bool isNebulaComponent(std::string name) {
        if (name == "Position") {
            return true;
        }
        if (name == "Scale") {
            return true;
        }
        if (name == "Quad") {
            return true;
        }
        if (name == "Sprite") {
            return true;
        }
        if (name == "Text") {
            return true;
        }
        if (name == "Color") {
            return true;
        }
        if (name == "Rotation") {
            return true;
        }
        return false;
    }

    static EntityId getLuaEntityId(lua_State *L, const int entIdIdx) {
        if (!lua_isnumber(L, 1)) {
            luaL_error(L, "Not a valid EntityID. Not a number.");
        }

        int entId = lua_tointeger(L, 1);

        if (entId < 0) {
            luaL_error(L, "Not a valid EntityID. Negative number.");
        }

        if (!ecs()->exists(entId)) {
            luaL_error(L, "Not a valid EntityID. Entity does not exists.");
        }

        return (EntityId) entId;
    }

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

    static int nebulaComponentConstructor(lua_State *L) {
        int argsCount = lua_gettop(L);

        if (argsCount == 0) {
            luaL_error(L, "An error occurred while instantiating a component. Use 'Component:new()' instead of 'Component.new()'.");
        }

        if (argsCount > 2) {
            luaL_error(L, "An error occurred while instantiating a component. Use 'Component:new()', 'Component:new(table)', 'Component()' or 'Component(table)'.");
        }

        if(!lua_getmetatable(L, 1)) {
            luaL_error(L, "An error occurred while instantiating a component. Use 'Component:new()' instead of 'Component.new()'.");
        }

        lua_getfield(L, -1, "__compId");
        ComponentId componentId = lua_tointeger(L, -1);
        lua_pop(L, 2);

        if (componentId == POSITION) {
            return positionConstructor(L, argsCount == 1);
        }
        if (componentId == SCALE) {
            return scaleConstructor(L, argsCount == 1);
        }
        if (componentId == QUAD) {
            return quadConstructor(L, argsCount == 1);
        }
        if (componentId == SPRITE) {
            return spriteConstructor(L, argsCount == 1);
        }
        if (componentId == TEXT) {
            return textConstructor(L, argsCount == 1);
        }
        if (componentId == COLOR) {
            return colorConstructor(L, argsCount == 1);
        }
        if (componentId == ROTATION) {
            return rotationConstructor(L, argsCount == 1);
        }

        return 1;
    }

    static void validateLuaComponent(lua_State *L, const int cTabIdx, ComponentValidationMethod cvm) {
        if (!lua_istable(L, cTabIdx) && !lua_isuserdata(L, cTabIdx)) {
            luaL_error(L, "An error occurred while finding a Component: Missing data. Check if the parameter is a nebula Component.");
        }
        if(!lua_getmetatable(L, cTabIdx)) {
            luaL_error(L, "An error occurred while finding a Component: Missing metatable. Check if the parameter is a nebula Component.");
        }
        // ..., metatable
        lua_getfield(L, -1, "__call");
        if (cvm == DEFINITION) {
            if (!lua_iscfunction(L, -1)) {
                luaL_error(L, "An error occurred while finding a Component: Missing metadata. Check if the parameter is a nebula Component.");
            }
        }
        if (cvm == INSTANCE) {
            if (!lua_isnil(L, -1)) {
                luaL_error(L, "An error occurred while finding a Component: Found wrong metadata. Check if the parameter is an instance of a nebula Component. Try using Component() instead of Component.");
            }
        }
        lua_pop(L, 2);
    }

    static ComponentId getLuaComponentMetadataId(lua_State *L, const int cTabIdx) {
        lua_getmetatable(L, cTabIdx);
        lua_getfield(L, -1, "__compId");
        if (!lua_isinteger(L, -1)) {
            luaL_error(L, "An error occurred while finding a Component: Missing metadata 'ID'. Check if the parameter is a nebula Component.");
        }
        ComponentId componentId = lua_tointeger(L, -1);
        lua_pop(L, 2);
        return componentId;
    }

    static const char *getLuaComponentMetadataName(lua_State *L, const int cTabIdx) {
        lua_getmetatable(L, cTabIdx);
        lua_getfield(L, -1, "__compName");
        if (!lua_isstring(L, -1)) {
            luaL_error(L, "An error occurred while finding a Component: Missing metadata 'Name'. Check if the parameter is a nebula Component.");
        }
        const char* componentName = lua_tostring(L, -1);
        lua_pop(L, 2);
        return componentName;
    }

    static ComponentId getLuaComponentId(lua_State *L, const int cTabIdx, const int metadataId, const char *metadataName) {
        ComponentId ecsCompId = ecs()->componentExists(metadataName);

        if (ecsCompId != metadataId) {
            luaL_error(L, "The Component does not match the ECS Registry. Check if the parameter is an instance of a registered Component.");
        }

        return ecsCompId;
    }

    template <typename T>
    static int addNebulaComponent(lua_State *L, const EntityId entId, const int cTabIdx, const ComponentId safeComponentId, const char *metadataName) {
        T *pointer = (T*)luaL_checkudata(L, cTabIdx, metadataName);
        if(pointer == nullptr) {
            lua_pushstring(L, metadataName);
            luaL_error(L, "Pointer to %s is a null pointer.");
        }
        ecs()->addComponentSafe(entId, safeComponentId, *pointer);
        return 0;
    }

    static int addLuaComponent(lua_State *L, const EntityId entId, const int cTabIdx) {
        validateLuaComponent(L, cTabIdx, INSTANCE);
        ComponentId metadataId = getLuaComponentMetadataId(L, cTabIdx);
        const char *metadataName = getLuaComponentMetadataName(L, cTabIdx);

        ComponentId safeComponentId = getLuaComponentId(L, cTabIdx, metadataId, metadataName);
    
        if (safeComponentId == POSITION) {
            return addNebulaComponent<Position>(L, entId, cTabIdx, safeComponentId, metadataName);
        }
        if (safeComponentId == SCALE) {
            return addNebulaComponent<Scale>(L, entId, cTabIdx, safeComponentId, metadataName);
        }
        if (safeComponentId == QUAD) {
            return addNebulaComponent<Quad>(L, entId, cTabIdx, safeComponentId, metadataName);
        }
        if (safeComponentId == SPRITE) {
            return addNebulaComponent<Sprite>(L, entId, cTabIdx, safeComponentId, metadataName);
        }
        if (safeComponentId == TEXT) {
            return addNebulaComponent<Text>(L, entId, cTabIdx, safeComponentId, metadataName);
        }
        if (safeComponentId == COLOR) {
            return addNebulaComponent<Color>(L, entId, cTabIdx, safeComponentId, metadataName);
        }
        if (safeComponentId == ROTATION) {
            return addNebulaComponent<Rotation>(L, entId, cTabIdx, safeComponentId, metadataName);
        }

        lua_pushvalue(L, cTabIdx); // pushes the table to create a ref
        ecs()->addComponentSafe(entId, safeComponentId, LuaTableRef{luaL_ref(L, LUA_REGISTRYINDEX)});

        return 0;
    }

    template <typename T>
    static int getNebulaComponent(lua_State *L, const EntityId entId, const ComponentId safeComponentId, const char *metadataName) {
        T* pointer = ecs()->getComponentSafe<T>(entId, safeComponentId);

        if (pointer == nullptr) {
            lua_pushstring(L, metadataName);
            lua_pushinteger(L, (int)entId);
            luaL_error(L, "The Component %s for Entity %i not found.");
        }

        lua_pushlightuserdata(L, pointer);
        luaL_getmetatable(L, metadataName);
        lua_setmetatable(L, -2);
        return 1;
    }

    static int getLuaComponent(lua_State *L, const EntityId entId, const int cTabIdx) {
        validateLuaComponent(L, cTabIdx, DEFINITION);

        ComponentId metadataId = getLuaComponentMetadataId(L, cTabIdx);
        const char *metadataName = getLuaComponentMetadataName(L, cTabIdx);

        ComponentId safeComponentId = getLuaComponentId(L, cTabIdx, metadataId, metadataName);

        if (safeComponentId == 0) {
            lua_pushstring(L, metadataName);
            luaL_error(L, "The Component %s does not exists anymore");
        }

        if (safeComponentId == POSITION) {
            return getNebulaComponent<Position>(L, entId, safeComponentId, metadataName);
        }
        if (safeComponentId == SCALE) {
            return getNebulaComponent<Scale>(L, entId, safeComponentId, metadataName);
        }
        if (safeComponentId == QUAD) {
            return getNebulaComponent<Quad>(L, entId, safeComponentId, metadataName);
        }
        if (safeComponentId == SPRITE) {
            return getNebulaComponent<Sprite>(L, entId, safeComponentId, metadataName);
        }
        if (safeComponentId == TEXT) {
            return getNebulaComponent<Text>(L, entId, safeComponentId, metadataName);
        }
        if (safeComponentId == COLOR) {
            return getNebulaComponent<Color>(L, entId, safeComponentId, metadataName);
        }
        if (safeComponentId == ROTATION) {
            return getNebulaComponent<Rotation>(L, entId, safeComponentId, metadataName);
        }

        LuaTableRef* tabRef = ecs()->getComponentSafe<LuaTableRef>(entId, safeComponentId);

        if (tabRef == nullptr) {
            lua_pushstring(L, metadataName);
            lua_pushinteger(L, (int)entId);
            luaL_error(L, "The Component %s for Entity %i not found.");
        }

        if (tabRef->luaRefBaseTable == LUA_NOREF) {
            lua_pushstring(L, metadataName);
            lua_pushinteger(L, (int)entId);
            luaL_error(L, "The Component %s for Entity %i does not exists anymore.");
        }

        lua_rawgeti(L, LUA_REGISTRYINDEX, tabRef->luaRefBaseTable);

        return 1;
    }

    static void removeLuaComponent(lua_State *L, const EntityId entId, const int cTabIdx) {
        validateLuaComponent(L, cTabIdx, DEFINITION);

        ComponentId metadataId = getLuaComponentMetadataId(L, cTabIdx);
        const char *metadataName = getLuaComponentMetadataName(L, cTabIdx);

        ComponentId safeComponentId = getLuaComponentId(L, cTabIdx, metadataId, metadataName);

        if (safeComponentId == 0) {
            lua_pushstring(L, metadataName);
            luaL_error(L, "The Component %s does not exists anymore");
        }

        if (!ecs()->hasComponentSafe(entId, safeComponentId)) {
            return;
        }

        LuaTableRef* tabRef = ecs()->getComponentSafe<LuaTableRef>(entId, safeComponentId);

        if (tabRef->luaRefBaseTable == LUA_NOREF) {
            lua_pushstring(L, metadataName);
            lua_pushinteger(L, (int)entId);
            luaL_error(L, "The Component %s for Entity %i does not exists anymore.");
        }

        luaL_unref(L, LUA_REGISTRYINDEX, tabRef->luaRefBaseTable);

        ecs()->removeComponentSafe<LuaTableRef>(entId, safeComponentId);
    }

    static void hasLuaComponent(lua_State *L, const EntityId entId, const int cTabIdx, bool *check) {
        validateLuaComponent(L, cTabIdx, DEFINITION);

        ComponentId metadataId = getLuaComponentMetadataId(L, cTabIdx);
        const char *metadataName = getLuaComponentMetadataName(L, cTabIdx);

        ComponentId safeComponentId = getLuaComponentId(L, cTabIdx, metadataId, metadataName);

        if (safeComponentId == 0) {
            lua_pushstring(L, metadataName);
            luaL_error(L, "The Component %s does not exists anymore");
        }

        *check = *check && ecs()->hasComponentSafe(entId, safeComponentId);
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
        const int numArgs = lua_gettop(L);
        if (numArgs == 0) {
            luaL_error(L, "Missing parameters");
        }
        const char *compName = luaL_checkstring(L, 1);
        if (isNebulaComponent(compName)) {
            if (numArgs > 1) {
                lua_pushstring(L, compName);
                luaL_error(L, "Component '%s' is already defined by Nebula, so it cannot be defined. Try using a different name or removing the second parameter.");
            }

            ComponentId compId = ecs()->componentExists(compName);
            if (!compId) {
                compId = ecs()->registerComponent(compName);
            }

            // table
            lua_newtable(L);
            // metatable
            lua_newtable(L);
            lua_pushcfunction(L, nebulaComponentConstructor);
            lua_setfield(L, -2, "__call");
            lua_pushinteger(L, compId);
            lua_setfield(L, -2, "__compId");
            lua_pushstring(L, compName);
            lua_setfield(L, -2, "__compName");
            lua_setmetatable(L, -2);

            lua_pushcfunction(L, nebulaComponentConstructor);
            lua_setfield(L, -2, "new");

            return 1;
        }
        luaL_checktype(L, 2, LUA_TTABLE);

        if (ecs()->componentExists(compName) != 0) {
            lua_pushstring(L, compName);
            luaL_error(L, "There already exists a component called '%s'.");
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
        EntityId entId = getLuaEntityId(L, 1);

        const int numArgs = lua_gettop(L);

        for (int i = 2; i <= numArgs; i ++) {
            addLuaComponent(L, entId, i);
        }

        return 0;
    }

    int w_getComponent(lua_State *L) {
        EntityId entId = getLuaEntityId(L, 1);

        const int numArgs = lua_gettop(L);

        int returnCount = 0;

        for (int i = 2; i <= numArgs; i ++) {
            returnCount += getLuaComponent(L, entId, i);
        }

        return returnCount;
    }

    int w_removeComponent(lua_State *L) {
        EntityId entId = getLuaEntityId(L, 1);

        const int numArgs = lua_gettop(L);

        for (int i = 2; i <= numArgs; i ++) {
            removeLuaComponent(L, entId, i);
        }

        return 0;
    }

    int w_hasComponent(lua_State *L) {
        EntityId entId = getLuaEntityId(L, 1);

        const int numArgs = lua_gettop(L);

        bool check = true;

        for (int i = 2; i <= numArgs; i ++) {
            hasLuaComponent(L, entId, i, &check);
        }

        lua_pushboolean(L, check);

        return 1;
    }

    int w_getEntitiesWith(lua_State *L) {
        const int numArgs = lua_gettop(L);

        lua_createtable(L, 0, 0);

        if (numArgs == 0) {
            return 1;
        }

        std::vector<ComponentId> components {};

        for (int i = 1; i <= numArgs; i ++) {
            validateLuaComponent(L, i, DEFINITION);

            ComponentId metadataId = getLuaComponentMetadataId(L, i);
            const char *metadataName = getLuaComponentMetadataName(L, i);

            components.emplace_back(getLuaComponentId(L, i, metadataId, metadataName));
        }

        std::vector<EntityId> entities = ecs()->getEntitiesWithSafe(components);

        if (entities.size() == 0) {
            return 1;
        }

        lua_pop(L, 1);

        lua_createtable(L, entities.size(), 0);
        for (int i = 0; i < entities.size(); i++) {
            lua_pushinteger(L, entities.at(i));
            lua_rawseti(L, -2, i);
        }

        return 1;
    }

    static const luaL_Reg functions[] = {
        {"spawn", w_spawn},
        {"print", w_print},
        {"component", w_component},
        {"addComponent", w_addComponent},
        {"getComponent", w_getComponent},
        {"removeComponent" , w_removeComponent},
        {"hasComponent", w_hasComponent},
        {"getEntitiesWith", w_getEntitiesWith},
        {0, 0}
    };

    static const lua_CFunction types[] = {
        nlua_ecs_position,
        nlua_ecs_scale,
        nlua_ecs_quad,
        nlua_ecs_sprite,
        nlua_ecs_text,
        nlua_ecs_color,
        nlua_ecs_rotation,
        0
    };

	extern "C" int nlua_ecs(lua_State *L) {
        World *ecs = ecs();

        WrapModule wModule;
        wModule.module = ecs;
        wModule.funcs = functions;
        wModule.types = types;

        return registerModule(L, wModule);
    }
} // ecs
} // nebula
