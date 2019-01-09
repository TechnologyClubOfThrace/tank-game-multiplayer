#include "shared_sprite_component.h"

SharedSpriteComponent::SharedSpriteComponent()
{
}

SharedSpriteComponent::~SharedSpriteComponent()
{
    int b=1;
}

void SharedSpriteComponent::FreeTextureMemory()
{
    int i = 0;
    //should not delete the texture from memory
    //because it is used in other textures too
}
