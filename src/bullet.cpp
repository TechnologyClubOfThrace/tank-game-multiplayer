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

Bullet::Bullet() : RotationAngle(0)
{

}

void Bullet::handleEvent(SDL_Event &e)
{

}

void Bullet::Update(std::chrono::milliseconds::rep deltaTime)
{

    //Move the dot left or right
    Position.x += Velocity.x * deltaTime ;

    //If the dot went too far to the left or right or touched a wall
    if( ( Position.x + level->camera.x < 0 ) || ( Position.x + DOT_WIDTH > level->tileMap.level_width) || touchesWall(level) )
    {
        //move back
        Position.x -= Velocity.x * deltaTime;

        //mark object for deletion
        Exists = false;
    }

    //Move the dot up or down
    Position.y += Velocity.y * deltaTime ;

    //If the dot went too far up or down or touched a wall
    if( ( Position.y + level->camera.y < 0 ) || ( Position.y + DOT_HEIGHT > level->tileMap.level_height) || touchesWall(level) )
    {
        //move back
        Position.y -= Velocity.y * deltaTime;

        //mark object for deletion
        Exists = false;
    }

}

void Bullet::setCamera( SDL_Rect& camera )
{
    /*
    //Center the camera over the dot
    camera.x = ( mBox.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( mBox.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds
    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
    */
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
            box.x = static_cast<int>(std::round(Position.x + level->camera.x));
            box.y = static_cast<int>(std::round(Position.y + level->camera.y));
            box.w = DOT_WIDTH;
            box.h = DOT_HEIGHT;

            if (SDL_HasIntersection(&box, &bb))
                return true;
        }
    }

    //If no wall tiles were touched
    return false;
}

void Bullet::Draw( SDL_Rect& camera )
{
    //Show the dot
    //gDotTexture.render( mBox.x - camera.x, mBox.y - camera.y );
    Texture.render(static_cast<int>(std::round(Position.x)),
                   static_cast<int>(std::round(Position.y)),
                   nullptr,
                   RotationAngle.CurrentAngle);
}
