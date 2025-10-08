#pragma once

#include "Definitions.hpp"

#include <unordered_map>
#include <typeinfo>
#include <string>
#include <set>

namespace nebula {
    namespace ecs {

struct EntityIdIndex {
    EntityId nextId;
    std::set<EntityId> unalivedIds;
};

inline EntityId getNewId(EntityIdIndex *index) {
    if (index->unalivedIds.size() != 0) {
        /* Use unalived id */
        EntityId id = *index->unalivedIds.begin();
        index->unalivedIds.erase(index->unalivedIds.begin());
        return id;
    }

    EntityId id = index->nextId ++;
    return id;
};

inline void setIdUnalived(EntityIdIndex *index, EntityId id) {
    index->unalivedIds.insert(id);
};

inline bool isIdUnalived(EntityIdIndex *index, EntityId id) {
    if (*index->unalivedIds.end() == id) {
        return true;
    }
    return *index->unalivedIds.find(id) == id;
};

struct ComponentIdIndex {
    ComponentId nextId = 1; //lazy way to check if a component exists, since no component will be registered with an id of 0
    std::unordered_map<std::string, ComponentId> typeIdIndex;
    std::unordered_map<std::string, std::string> typeNameIndex;
    std::unordered_map<ComponentId, std::string> idNameIndex;
};

template <typename T>
inline ComponentId getNewId(ComponentIdIndex *index) {
    ComponentId id = index->nextId ++;
    std::string name = std::string(typeid(T).name());
    index->typeIdIndex.insert({name, id});
    index->idNameIndex.insert({id, name});
    return id;
};

inline ComponentId getNewId(ComponentIdIndex *index, const char* componentName) {
    ComponentId id = index->nextId ++;
    std::string s = componentName;
    index->typeIdIndex.insert({s, id});
    index->idNameIndex.insert({id, s});
    return id;
};

template <typename T>
inline ComponentId getNewId(ComponentIdIndex *index, const char* componentName) {
    ComponentId id = index->nextId ++;
    std::string typeName = std::string(typeid(T).name());
    std::string s = componentName;
    index->typeIdIndex.insert({s, id});
    index->typeNameIndex.insert({typeName, s});
    index->idNameIndex.insert({id, s});
    return id;
};

template <typename T>
inline ComponentId getComponentId(ComponentIdIndex *index) {
    std::string name = std::string(typeid(T).name());
    if (index->typeIdIndex.count(name) == 0) {
        if (index->typeNameIndex.count(name) == 0){
            return 0;
        }
        if (index->typeIdIndex.count(index->typeNameIndex.at(name)) == 0) {
            return 0;
        }
        return index->typeIdIndex[index->typeNameIndex[name]];
    }
    return index->typeIdIndex[name];
};

inline ComponentId getComponentId(ComponentIdIndex *index, const char* componentName) {
    std::string s = componentName;
    if (index->typeIdIndex.count(s) == 0) {
        return 0;
    }
    return index->typeIdIndex[s];
};

inline std::string getComponentName(ComponentIdIndex *index, ComponentId cId) {
    if (index->idNameIndex.count(cId) == 0) {
        return "";
    }
    return index->idNameIndex[cId];
};


struct TableIdIndex {
    TableId nextId;
    std::unordered_map<TypeHash, TableId> typeHashIndex;
};

inline TableId getNewId(TableIdIndex *index, TypeHash th) {
    TableId id = index->nextId ++;
    index->typeHashIndex.insert({th, id});
    return id;
};

inline TableId getId(TableIdIndex *index, TypeHash th) {
    return index->typeHashIndex.at(th);
};

inline bool hasId(TableIdIndex *index, TypeHash th) {
    return index->typeHashIndex.count(th) != 0;
};

}// ecs
}// nebula