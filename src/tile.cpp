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

void Tile::render()
{
    if (SDL_HasIntersection(&game::viewports[0].camera.frame, &this->mBox) == SDL_TRUE){

        SDL_Rect target_rect;
        target_rect.x = this->mBox.x - game::viewports[0].camera.frame.x;
        target_rect.y = this->mBox.y - game::viewports[0].camera.frame.y;
        target_rect.w = sprite.rect.w;
        target_rect.h = sprite.rect.h;


        SDL_RenderCopyEx(sprite.spritesheet_texture->WindowRenderer,
                         sprite.spritesheet_texture->mTexture,
                         &sprite.rect,
                         &target_rect,0, nullptr, SDL_FLIP_NONE);
    }
}

void Tile::render_radar()
{
    SDL_Rect target_rect;
    target_rect.x = static_cast<int>(round(game::viewports[1].frame.x + this->mBox.x/10));
    target_rect.y = static_cast<int>(round(game::viewports[1].frame.y + this->mBox.y/10));
    target_rect.w = static_cast<int>(round(sprite.rect.w/10));
    target_rect.h = static_cast<int>(round(sprite.rect.h/10));

    SDL_SetTextureBlendMode(sprite.spritesheet_texture->mTexture, SDL_BLENDMODE_BLEND);

    sprite.spritesheet_texture->setAlpha(80);
    SDL_RenderCopyEx(sprite.spritesheet_texture->WindowRenderer,
                     sprite.spritesheet_texture->mTexture,
                     &sprite.rect,
                     &target_rect,0, nullptr, SDL_FLIP_NONE);
     sprite.spritesheet_texture->setAlpha(255);

}



SDL_Rect Tile::getBox()
{
    return mBox;
}
