#include "unified_tiles_entity.h"

UnifiedTilesEntity::UnifiedTilesEntity()
{
    transform_component = std::make_unique<TransformComponent>();
    sprite_component = std::make_unique<SpriteComponent>();
    viewport_component = std::make_unique<ViewportComponent>(0);
    //collider2d_collection_component = std::make_unique<Collider2DCollectionComponent>();
}
