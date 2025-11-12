#pragma once

#include "../common/Module.hpp"
#include "../ecs/Components.hpp"
#include "../ecs/World.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace nebula {
    namespace physics {

struct AABB {
    float left, right, top, bottom;
};

class Physics : public Module {
public:
    Physics(ecs::World* world);

    bool checkCollision(ecs::EntityId e1, ecs::EntityId e2);

    bool checkCollision(float x, float y, ecs::EntityId entity);

private:
    AABB getTransformedAABB(ecs::EntityId entity);
    glm::vec2 rotatePoint(const glm::vec2& point, float angle, const glm::vec2& origin);

    ecs::World* world;
};

} // physics
} // nebula
