#include "collision_system.h"

CollisionSystem::CollisionSystem()
{

}

void CollisionSystem::UpdateColliderFromTransform(PointCollider2D *pointCollider2D, const std::unique_ptr<TransformComponent> &transform_component)
{
    pointCollider2D->point = transform_component->Position;
}
void CollisionSystem::UpdateColliderFromTransform(RectangleCollider2D *rectangleCollider2D, const std::unique_ptr<TransformComponent> &transform_component)
{
    rectangleCollider2D->rectangle.setXY(transform_component->Position);
}

CollisionSystemResult CollisionSystem::DetectAndRespond(const Entity &entity, const std::vector<std::unique_ptr<Entity>>::iterator in_it)
{
    //todo: because most entites contain one collider, we might first check for collisions on the first collider of both colliders without using a for loop. Should measure the performance first
    //first of all update the collider points
    //By default any collider2d_collection_component with isCollisionChecker = true
    //should update its colliders based on the entity tranform.
    //TODO: update all colliders, not only the [0] of the array like we are doing now
    for (const auto& collider2d : entity.collider2d_collection_component->colliders){
        //todo: rect and polygon colliders transform
        if (collider2d->collider2DType == Collider2DType::PointCollider2D){
            CollisionSystem::UpdateColliderFromTransform((static_cast<PointCollider2D*>(collider2d.get())), entity.transform_component);
        }
        else if (collider2d->collider2DType == Collider2DType::RectangleCollider2D){
            CollisionSystem::UpdateColliderFromTransform((static_cast<RectangleCollider2D*>(collider2d.get())), entity.transform_component);
        }
    }

    //check collisions for every entity object with a collider component that allowsCollisionCheck
    //and it is not the same entity with the current CollisionChecker
    for(auto it = game::entityObjects.begin(); it != game::entityObjects.end();)
    {
        if (in_it != it && ((*it)->collider2d_collection_component != nullptr && (*it)->collider2d_collection_component->allowsCollisionCheck)){
            //check every collider of every entity
            for (const auto& otherCollider : (*it)->collider2d_collection_component->colliders){
                for (const auto& checkerCollider2d : entity.collider2d_collection_component->colliders) {
                    //check if there is a collision
                    if (CollisionSystem::AreColliding(checkerCollider2d, otherCollider)){
                        //There is a collision. Now depending on the collisionResponse of
                        //the checker collider, do the appropriate thing with the entity or the tranform
                        if(checkerCollider2d->collisionResponse == CollisionRespose::RemoveEntity){
                            entity.properties_component->shouldBeRemoved = true;
                        }
                        else if (checkerCollider2d->collisionResponse == CollisionRespose::CollideAndSlide){
                            return CollisionSystemResult::RevertTransform;
                        }
                        return CollisionSystemResult::DoNothing;
                    }
                }
            }

        }

        it++;
    }//for auto it...
    return CollisionSystemResult::DoNothing;
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
    else if (checkerCollider->collider2DType == Collider2DType::RectangleCollider2D && otherCollider->collider2DType == Collider2DType::RectangleCollider2D) {
        return CollisionSystem::AreColliding(*static_cast<RectangleCollider2D*>(otherCollider.get()), *static_cast<RectangleCollider2D*>(checkerCollider.get()));
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


