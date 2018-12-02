/* ***********************************************************************
 * Tank Game Multiplayer
 * (C) 2018 by Yiannis Bourkelis (hello@andama.org)
 *
 * This file is part of Tank Game Multiplayer.
 *
 * Tank Game Multiplayer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank Game Multiplayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tank Game Multiplayer.  If not, see <http://www.gnu.org/licenses/>.
 * ***********************************************************************/

#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H

#include <SDL.h>
#include <string>
#include <SDL_ttf.h>

class TextureWrapper
{
public:
    TextureWrapper();

    //Deallocates memory
    ~TextureWrapper();

    //Loads image at specified path
    bool loadFromFile( std::string path );

    #ifdef _SDL_TTF_H
    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    #endif

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int getWidth();
    int getHeight();

    //The window renderer
    SDL_Renderer* WindowRenderer = nullptr;
    TTF_Font * font = nullptr;

    //The actual hardware texture
    SDL_Texture* mTexture;
private:

    //Image dimensions
    int mWidth = 0;
    int mHeight = 0;
};

#endif // TEXTURE_WRAPPER_H
