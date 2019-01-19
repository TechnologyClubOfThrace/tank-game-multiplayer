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

void CollisionSystem::DetectAndRespond(const Entity &entity, const std::vector<std::unique_ptr<Entity>>::iterator in_it)
{
    //todo: because most entites contain one collider, we might first check for collisions on the first collider of both colliders without using a for loop. Should measure the performance first

    if (entity.collider2d_collection_component->isCollisionChecker) {
        //first of all update the collider points
        //By default any collider2d_collection_component with isCollisionChecker = true
        //should update its colliders based on the entity tranform.
        //TODO: update all colliders, not only the [0] of the array like we are doing now
        if (entity.collider2d_collection_component->colliders[0]->collider2DType == Collider2DType::PointCollider2D){
            auto p = static_cast<PointCollider2D*>(entity.collider2d_collection_component->colliders[0].get());
            p->point = entity.transform_component->Position;
        }

        //check collisions for every entity object with a collider component that allowsCollisionCheck
        //and it is not the same entity with the current CollisionChecker
        for(auto it = game::entityObjects.begin(); it != game::entityObjects.end();)
        {
            if (in_it != it && ((*it)->collider2d_collection_component != nullptr && (*it)->collider2d_collection_component->allowsCollisionCheck)){
                //check every collider of every entity
                for (const auto& otherCollider : (*it)->collider2d_collection_component->colliders){
                    for (const auto& checkerCollider2d : entity.collider2d_collection_component->colliders) {
                        if (CollisionSystem::AreColliding(checkerCollider2d, otherCollider)){
                            //TODO: now on collision only marks an entity as shouldBeRemoved
                            //We should change this, because this is valid only for bullets
                            entity.properties_component->shouldBeRemoved = true;
                            return;
                        }
                    }
                }

            }

            it++;
        }//for auto it...

    } //isCollisionChecker
}

//Based on the type of the two input colliders, calls the appropriate collision checking algorithm
bool CollisionSystem::AreColliding(const std::unique_ptr<Collider2D>& checkerCollider, const std::unique_ptr<Collider2D>&  otherCollider)
{
    if (checkerCollider->collider2DType == Collider2DType::ConvexPolygonColider2D && otherCollider->collider2DType == Collider2DType::ConvexPolygonColider2D) {
        return CollisionSystem::AreColliding(*static_cast<ConvexPolygonCollider2D*>(checkerCollider.get()), *static_cast<ConvexPolygonCollider2D*>(otherCollider.get()));
    }
    else if (checkerCollider->collider2DType == Collider2DType::ConvexPolygonColider2D && otherCollider->collider2DType == Collider2DType::RectangleCollider2D) {
        return CollisionSystem::AreColliding(*static_cast<ConvexPolygonCollider2D*>(checkerCollider.get()), *static_cast<RectangleCollider2D*>(otherCollider.get()));
    }
    else if (checkerCollider->collider2DType == Collider2DType::PointCollider2D && otherCollider->collider2DType == Collider2DType::ConvexPolygonColider2D) {
        return CollisionSystem::AreColliding(*static_cast<ConvexPolygonCollider2D*>(otherCollider.get()), *static_cast<PointCollider2D*>(checkerCollider.get()));
    }
    else if (checkerCollider->collider2DType == Collider2DType::PointCollider2D && otherCollider->collider2DType == Collider2DType::RectangleCollider2D) {
        return CollisionSystem::AreColliding(*static_cast<RectangleCollider2D*>(otherCollider.get()), *static_cast<PointCollider2D*>(checkerCollider.get()));
    }

    return false;
}

/* Bellow are the Collision checking algorithms
 * **********************************************
 */
bool CollisionSystem::AreColliding(const ConvexPolygonCollider2D& convexCollider2d_1, const ConvexPolygonCollider2D& convexCollider2d_2)
{
    return false;
}

bool CollisionSystem::AreColliding(const ConvexPolygonCollider2D& convexCollider2d, const RectangleCollider2D& rectangleCollider2d)
{
    return false;
}

bool CollisionSystem::AreColliding(const ConvexPolygonCollider2D& convexCollider2d, const PointCollider2D& pointCollider2d)
{
    return false;
}

bool CollisionSystem::AreColliding(const RectangleCollider2D& rectangleCollider2d_1, const RectangleCollider2D& rectangleCollider2d_2)
{
    if (rectangleCollider2d_1.rectangle.getX() > rectangleCollider2d_2.rectangle.getRight()){
        return false;
    }
    else if (rectangleCollider2d_1.rectangle.getY() > rectangleCollider2d_2.rectangle.getBottom()){
        return false;
    }
    else if (rectangleCollider2d_1.rectangle.getRight() < rectangleCollider2d_2.rectangle.getX()){
        return false;
    }
    else if (rectangleCollider2d_1.rectangle.getBottom() < rectangleCollider2d_2.rectangle.getY()){
        return false;
    }

    return true;
}

bool CollisionSystem::AreColliding(const RectangleCollider2D& rectangleCollider2d, const PointCollider2D& pointCollider2d)
{
    if (pointCollider2d.point.x < rectangleCollider2d.rectangle.getX() || pointCollider2d.point.x > rectangleCollider2d.rectangle.getRight()){
        return false;
    }
    else if (pointCollider2d.point.y < rectangleCollider2d.rectangle.getY() || pointCollider2d.point.y > rectangleCollider2d.rectangle.getBottom()){
        return false;
    }

    return true;
}

bool CollisionSystem::AreColliding(const PointCollider2D& pointCollider2d_1, const PointCollider2D& pointCollider2d_2)
{
    return pointCollider2d_1 == pointCollider2d_2;
}


