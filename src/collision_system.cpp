#include "collision_system.h"

CollisionSystem::CollisionSystem()
{

}

void CollisionSystem::DetectAndRespond(const Entity &entity)
{
    if (entity.transform_component->Position.x > ViewPort::levelWidth ||
        entity.transform_component->Position.x < 0 ||
        entity.transform_component->Position.y > ViewPort::levelHeight ||
        entity.transform_component->Position.y < 0) {
        entity.properties_component->shouldBeRemoved = true;
    }
}
