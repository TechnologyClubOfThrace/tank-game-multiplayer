#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "transform_component.h"
#include "sprite_component.h"
#include "viewport.h"

class RenderSystem
{
public:
    RenderSystem();
    void Render(TransformComponent &transformComponent, SpriteComponent &spriteComponent, std::vector<ViewPort> &viewports);
    static bool CreateTextureFromFile(std::string path, SDL_Renderer *renderer, SpriteComponent &spriteComponent);

    SDL_Renderer * renderer;
};

#endif // RENDER_SYSTEM_H
