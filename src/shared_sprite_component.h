#ifndef SHARED_SPRITE_COMPONENT_H
#define SHARED_SPRITE_COMPONENT_H

#include "sprite_component.h"

class SharedSpriteComponent : public SpriteComponent
{
public:
    SharedSpriteComponent();
    static SDL_Texture * shared_texture;
};

#endif // SHARED_SPRITE_COMPONENT_H
