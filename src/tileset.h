#ifndef TILESET_H
#define TILESET_H

#include <string>
#include <SDL.h>
#include "texture_wrapper.h"

class TileSet
{
public:
    TileSet();

    std::string tsx_fileName {};
    std::string image_fileName {};
    int tileCount {};
    int columns {};
    int tileWidth {};
    int tileHeight {};
    int spacing {};
    TextureWrapper textureWrapper {};
};

#endif // TILESET_H
