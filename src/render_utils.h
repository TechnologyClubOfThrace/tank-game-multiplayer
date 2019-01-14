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

    static bool LoadTextureFromFile(const std::string &path, SDL_Texture *&texture);
    static bool LoadTextureFromFile(const std::string &path, SpriteComponent &spriteComponent);
    static void setColor(SDL_Texture *&texture, Uint8 red, Uint8 green, Uint8 blue);
    static void setBlendMode(SDL_Texture *&texture, SDL_BlendMode blending);
    static void setAlpha(SDL_Texture *&texture, Uint8 alpha);
    static void createBlankTexture(const int width, const int height, SDL_Texture *&texture, const bool setAsTargetRenderer, Uint32 pixelFormat);
    static bool LoadSpriteFromFile(const std::string &path, SpriteComponent &sprite);
};

#endif // RENDER_UTILS_H
