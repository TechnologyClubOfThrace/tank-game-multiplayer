#include "shared_sprite_component.h"

SharedSpriteComponent::SharedSpriteComponent()
{
}

SharedSpriteComponent::~SharedSpriteComponent()
{

}

void SharedSpriteComponent::FreeTextureMemory()
{
    //should not delete the texture from memory
    //because it is used in other textures too
}
