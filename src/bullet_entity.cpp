#include "bullet_entity.h"

BulletEntity::BulletEntity()
{
    //create required components for the tank entity
    transform_component = std::make_unique<TransformComponent>();//transform / position related
    sprite_component = std::make_unique<SpriteComponent>();//appearance - rendering system,
    //rigid_body2d_component = std::make_unique<RigidBody2DComponent>();//physics
    collider2d_collection_component = std::make_unique<Collider2DCollectionComponent>();//collision shapes
    viewport_component = std::make_unique<ViewportComponent>(0);//alternative viewport rendering
    viewport_component->movesTheCamera = false;
    viewport_component->viewports[0].movesTheCamera = false;
}
