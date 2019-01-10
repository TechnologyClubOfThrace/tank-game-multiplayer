#include "bullet_entity.h"

SpriteComponent BulletEntity::m_bullet_sprite_component;

BulletEntity::BulletEntity()
{
    //create required components for the tank entity
    transform_component = std::make_unique<TransformComponent>();//transform / position related
    sprite_component = std::make_unique<SpriteComponent>();//appearance - rendering system
    rigid_body2d_component = std::make_unique<RigidBody2DComponent>();//physics
    collider2d_collection_component = std::make_unique<Collider2DCollectionComponent>();//collision shapes
    viewport_component = std::make_unique<ViewportComponent>(0);//target viewport rendering

    //reuse the bullet sprite component
    if(BulletEntity::m_bullet_sprite_component.texture == nullptr){
        RenderUtils::LoadSpriteFromFile("bullet_w65h20.png", BulletEntity::m_bullet_sprite_component);
    }
    *sprite_component = BulletEntity::m_bullet_sprite_component;
}
