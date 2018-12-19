#ifndef TILESET_H
#define TILESET_H

#include <string>
#include <SDL.h>

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
    SDL_Texture * texture = nullptr;
};

#endif // TILESET_H
