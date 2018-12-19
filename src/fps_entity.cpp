#include "fps_entity.h"

FpsEntity::FpsEntity()
{
    transform_component = std::make_unique<TransformComponent>();
    sprite_component = std::make_unique<SpriteComponent>();
    sprite_component->renderPositionRelatedToCamera = true;
}
