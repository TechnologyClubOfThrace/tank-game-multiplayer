#include "collision_system.h"

CollisionSystem::CollisionSystem()
{

}

/*
void CollisionSystem::DetectAndRespond(const Entity &entity)
{
    if (entity.transform_component->Position.x > ViewPort::levelWidth ||
        entity.transform_component->Position.x < 0 ||
        entity.transform_component->Position.y > ViewPort::levelHeight ||
        entity.transform_component->Position.y < 0) {
        entity.properties_component->shouldBeRemoved = true;
    }
}
*/

void CollisionSystem::DetectAndRespond(const Entity &entity)
{
    if (entity.collider2d_collection_component->isCollisionChecker) {
        for (auto& collider2d : entity.collider2d_collection_component->colliders) {
            if (collider2d.collider2DType == Collider2DType::PointCollider2D) {
                PointCollider2D pointCollider2d = static_cast<PointCollider2D>(collider2d);
                if (collider2d->Position.x > ViewPort::levelWidth ||
                    entity.transform_component->Position.x < 0 ||
                    entity.transform_component->Position.y > ViewPort::levelHeight ||
                    entity.transform_component->Position.y < 0) {
                    entity.properties_component->shouldBeRemoved = true;
                }
            }
        }
    }
}
