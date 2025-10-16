#include "Physics.hpp"

namespace nebula {
    namespace physics {

Physics::Physics(ecs::World* world) : Module(PHYSICS, "physics"), world(world) {}

bool Physics::checkCollision(ecs::EntityId e1, ecs::EntityId e2) {
    if (!world->hasComponent<Position>(e1) || !world->hasComponent<CollisionBox>(e1) ||
        !world->hasComponent<Position>(e2) || !world->hasComponent<CollisionBox>(e2)) {
        return false;
    }

    AABB box1 = getTransformedAABB(e1);
    AABB box2 = getTransformedAABB(e2);

    return !(box1.right < box2.left || box1.left > box2.right || box1.bottom < box2.top || box1.top > box2.bottom);
}


AABB Physics::getTransformedAABB(ecs::EntityId entity) {
    Position* pos = world->getComponent<Position>(entity);
    CollisionBox* collision = world->getComponent<CollisionBox>(entity);
    Scale* scale = world->getComponent<Scale>(entity);
    Rotation* rotation = world->getComponent<Rotation>(entity);

    float width = collision->width;
    float height = collision->height;
    float offsetX = collision->x;
    float offsetY = collision->y;

    if (scale) {
        width *= scale->x;
        height *= scale->y;
        offsetX *= scale->x;
        offsetY *= scale->y;
    }

    AABB aabb;

    // if doesnt have rotation, use simple AABB
    if (!rotation || rotation->value == 0.0f) {

        aabb.left = pos->x + offsetX;
        aabb.right = pos->x + offsetX + width;
        aabb.top = pos->y + offsetY;
        aabb.bottom = pos->y + offsetY + height;

    } else {

        float rotationAngle = glm::radians(rotation->value);
        glm::vec2 center(pos->x + offsetX + width / 2.0f, pos->y + offsetY + height / 2.0f);

        // calculate each corner
        glm::vec2 corners[4] = {
            {pos->x + offsetX, pos->y + offsetY},
            {pos->x + offsetX + width, pos->y + offsetY},
            {pos->x + offsetX + width, pos->y + offsetY + height},
            {pos->x + offsetX, pos->y + offsetY + height}
        };

        // rotate corners
        for (int i = 0; i < 4; i++) {
            corners[i] = rotatePoint(corners[i], rotationAngle, center);
        }

        // find min/max
        aabb.left = aabb.right = corners[0].x;
        aabb.top = aabb.bottom = corners[0].y;

        for (int i = 1; i < 4; i++) {
            aabb.left = std::min(aabb.left, corners[i].x);
            aabb.right = std::max(aabb.right, corners[i].x);
            aabb.top = std::min(aabb.top, corners[i].y);
            aabb.bottom = std::max(aabb.bottom, corners[i].y);
        }
    }

    return aabb;
}

glm::vec2 Physics::rotatePoint(const glm::vec2& point, float rotationAngle, const glm::vec2& origin) {
    glm::vec2 translated = point - origin;

    float cosA = std::cos(rotationAngle);
    float sinA = std::sin(rotationAngle);

    glm::vec2 rotated;
    rotated.x = translated.x * cosA - translated.y * sinA;
    rotated.y = translated.x * sinA + translated.y * cosA;

    return rotated + origin;
}

} // physics
} // nebula
