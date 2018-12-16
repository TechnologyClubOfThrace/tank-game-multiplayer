#include "tile_entity.h"

TileEntity::TileEntity()
{
    transform_component = std::make_unique<TransformComponent>();
    sprite_component = std::make_unique<SharedSpriteComponent>();
}
