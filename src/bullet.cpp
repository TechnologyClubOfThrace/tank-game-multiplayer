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

#include "bullet.h"
#include <cmath>
#include "game.h"

Bullet::Bullet()
{
}

void Bullet::Update(std::chrono::milliseconds::rep deltaTime)
{

    //Move the dot left or right
    transform.Position.x += Velocity.x * deltaTime ;

    //If the dot went too far to the left or right or touched a wall
    if( ( transform.Position.x < 0 ) || ( transform.Position.x + DOT_WIDTH > level->tileMap.level_width) || touchesWall(level) )
    {
        //move back
        transform.Position.x -= Velocity.x * deltaTime;

        //mark object for deletion
        Exists = false;
    }

    //Move the dot up or down
    transform.Position.y += Velocity.y * deltaTime ;

    //If the dot went too far up or down or touched a wall
    if( ( transform.Position.y < 0 ) || ( transform.Position.y + DOT_HEIGHT > level->tileMap.level_height) || touchesWall(level) )
    {
        //move back
        transform.Position.y -= Velocity.y * deltaTime;

        //mark object for deletion
        Exists = false;
    }

}

bool Bullet::touchesWall(Level* level)
{
    //Go through the tiles
    for( size_t i = 0; i < level->Tiles.size(); ++i )
    {
        //If the tile is a wall type tile
        if( !(level->Tiles[i].sprite.index == 4))
        {
            auto bb = level->Tiles[i].getBox();//todo
            SDL_Rect box;
            box.x = static_cast<int>(std::round(transform.Position.x));
            box.y = static_cast<int>(std::round(transform.Position.y));
            box.w = DOT_WIDTH;
            box.h = DOT_HEIGHT;

            if (SDL_HasIntersection(&box, &bb))
                return true;
        }
    }

    //If no wall tiles were touched
    return false;
}

void Bullet::Draw()
{
    texture.render(static_cast<int>(std::round(transform.Position.x - game::viewports[0].camera.frame.x)),
                   static_cast<int>(std::round(transform.Position.y - game::viewports[0].camera.frame.y)),
                   nullptr,
                   RotationAngle.CurrentAngleDegrees);
}

void Bullet::Draw(size_t viewportIndex)
{
    if (viewportIndex != 1) return;

    SDL_Rect source_rect;
    source_rect.x = 0;
    source_rect.y = 0;
    source_rect.w = static_cast<int>(round(texture.getWidth()));
    source_rect.h = static_cast<int>(round(texture.getHeight()));

    SDL_Rect dest_rect;
    dest_rect.x = static_cast<int>(round(game::viewports[viewportIndex].frame.x + transform.Position.x/10));
    dest_rect.y = static_cast<int>(round(game::viewports[viewportIndex].frame.y + transform.Position.y/10));
    dest_rect.w = static_cast<int>(round(texture.getWidth()/10));
    dest_rect.h = static_cast<int>(round(texture.getHeight()/10));

    SDL_RenderCopyEx(texture.WindowRenderer,
                      texture.mTexture,
                      &source_rect,
                      &dest_rect,
                      RotationAngle.CurrentAngleDegrees,
                      nullptr,SDL_FLIP_NONE);
}
