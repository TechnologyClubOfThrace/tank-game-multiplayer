#include "fps_entity.h"

FpsEntity::FpsEntity()
{
    transform_component = std::make_unique<TransformComponent>();
    sprite_component = std::make_unique<SpriteComponent>();
    viewport_component = std::make_unique<ViewportComponent>(2);
    sprite_component->renderPositionRelatedToCamera = true;

    //viewport_component->viewports[0].
}
