#ifndef RENDER_UTILS_H
#define RENDER_UTILS_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "sprite_component.h"

class RenderUtils
{
public:
    RenderUtils();

    static SDL_Renderer* windowRenderer;

    static bool LoadTextureFromFile(std::string path, SDL_Texture *&texture);
    static bool LoadTextureFromFile(std::string path, SpriteComponent &spriteComponent);
    static void setColor(SDL_Texture *&texture, Uint8 red, Uint8 green, Uint8 blue);
    static void setBlendMode(SDL_Texture *&texture, SDL_BlendMode blending);
    static void setAlpha(SDL_Texture *&texture, Uint8 alpha);
};

#endif // RENDER_UTILS_H
