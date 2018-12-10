#include "sprite_component.h"

SpriteComponent::SpriteComponent()
{

}

SpriteComponent::~SpriteComponent()
{
    if( texture != nullptr )
    {
        SDL_DestroyTexture(texture);
    }
}
