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

#include "tile.h"

Tile::Tile(int x, int y, int w, int h)
{
    //Get the offsets
    //these are the x and y location where the tile exisits inside the game map
    mBox.x = x;
    mBox.y = y;
    mBox.w = w;
    mBox.h = h;
}

void Tile::render( SDL_Rect& camera )
{
    //Show the tile
    //gTileTexture.render( mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ] );
    sprite.spritesheet_texture->render(
                mBox.x,
                mBox.y,
                &sprite.rect);
}

SDL_Rect Tile::getBox()
{
    return mBox;
}
