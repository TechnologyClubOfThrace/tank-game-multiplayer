#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include "transform_component.h"
#include "sprite_component.h"

class Entity
{
public:
    Entity();
    ~Entity();

    //component flags
    bool hasTransformComponent = false;
    bool hasSpriteComponent = false;

    //components
    std::unique_ptr<TransformComponent> transform_component;
    std::unique_ptr<SpriteComponent> sprite_component;
};

#endif // ENTITY_H
