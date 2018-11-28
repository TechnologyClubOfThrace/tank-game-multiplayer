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

#include "snake_food.h"


SnakeFood::SnakeFood()
{
    //Initialize the collision box
    mBox.x = random(40,600);
    mBox.y = random(40,440);
    mBox.w = DOT_WIDTH;
    mBox.h = DOT_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void SnakeFood::handleEvent(SDL_Event &e)
{

}

void SnakeFood::Update(std::chrono::milliseconds::rep deltaTime)
{
    alpha += alpha_Vel * (deltaTime/2);
    if (alpha <= 150){
        alpha_Vel = 1;
    } else if (alpha >= 200){
        alpha_Vel = -1;
    }

    snakeFoodTexture.setAlpha(alpha);
}


void SnakeFood::move(Level& level, double deltaTime)
{
    //Move the dot left or right
    mBox.x += mVelX * (deltaTime*mDOT_SPEED) ;


    //Move the dot up or down
    mBox.y += mVelY * (deltaTime*mDOT_SPEED) ;
}


void SnakeFood::Draw()
{
    //Show the dot
    //gDotTexture.render( mBox.x - camera.x, mBox.y - camera.y );
    snakeFoodTexture.render(mBox.x, mBox.y);
}

int SnakeFood::random(int min, int max) {
  return rand() % (max - min + 1) + min;
}
