#include "fps_entity.h"

FpsEntity::FpsEntity()
{
    transform_component = std::make_unique<TransformComponent>();
    sprite_component = std::make_unique<SpriteComponent>();
    target_viewport_component = std::make_unique<TargetViewportComponent>(2);
}
