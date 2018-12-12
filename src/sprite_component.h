#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <SDL.h>
#include <memory>
#include "component.h"

class SpriteComponent : Component
{
public:
    SpriteComponent();
    ~SpriteComponent();

    SDL_Rect rect;
    SDL_Texture * texture = nullptr;
};

#endif // SPRITE_COMPONENT_H
