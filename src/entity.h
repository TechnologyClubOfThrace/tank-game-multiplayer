#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include "transform_component.h"
#include "sprite_component.h"
#include "tank_input_component.h"
#include "rigid_body2d_component.h"

class Entity
{
public:
    Entity();
    ~Entity();

    //component flags
    bool hasTransformComponent = false;
    bool hasSpriteComponent = false;
    bool hasTankInputComponent = false;
    bool hasRigidBody2DComponent = false;

    //components
    std::unique_ptr<TransformComponent> transform_component;
    std::unique_ptr<SpriteComponent> sprite_component;
    std::unique_ptr<TankInputComponent> tank_input_component;
    std::unique_ptr<RigidBody2DComponent> rigid_body2d_component;
};

#endif // ENTITY_H
