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

#ifndef SNAKE_FOOD_H
#define SNAKE_FOOD_H

#include <SDL.h>
#include "level.h"
#include "game_object.h"

class SnakeFood : public GameObject
{
public:
    SnakeFood();

    void handleEvent(SDL_Event &e);
    void Update(std::chrono::milliseconds::rep deltaTime);
    void Draw(SDL_Rect &camera);

    void move(Level &level, double deltaTime);
    //The dimensions of the dot
    static const int DOT_WIDTH = 32;
    static const int DOT_HEIGHT = 32;
    //Maximum axis velocity of the dot
    static const int DOT_VEL = 2;

    TextureWrapper snakeFoodTexture;

    int random(int min, int max);
private:
    //Collision box of the dot
    SDL_Rect mBox;

    //The velocity of the dot
    int mVelX, mVelY;

    double mDOT_SPEED = 1.5;

    int alpha = 255;
    int alpha_Vel = -1;
};

#endif // SNAKE_FOOD_H
