#include "tile_entity.h"

TileEntity::TileEntity()
{
    transform_component = std::make_unique<TransformComponent>();
    sprite_component = std::make_unique<SpriteComponent>(TexturePointerHandler::KeepTexturePointer);
    target_viewport_component = std::make_unique<TargetViewportComponent>(0);
}
