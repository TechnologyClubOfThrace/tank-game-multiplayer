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

#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include "texture_wrapper.h"
#include "level.h"
#include "vector2d.h"
#include "vector2d_angle.h"
#include "keystate.h"
#include "game_object.h"


class Snake : public GameObject
{
public:
    Snake();
    void handleEvent(SDL_Event &e);
    void Draw(SDL_Rect &camera);
    void Update(std::chrono::milliseconds::rep deltaTime);

    void setCamera(SDL_Rect &camera);
    void FireBullet();

    KeyState keystate;

    //The dimensions of the dot
    static const int DOT_WIDTH = 133;
    static const int DOT_HEIGHT = 50;

    double NormalTankSpeed = 0.13;
    double FastTankSpeedMultiplier = 3.50;
    AngleDirection TankDirection = AngleDirection::Forward;
    AngleDirection TankDirectionBeforeStopping = AngleDirection::Forward;

    TextureWrapper snakeTexture;

    Level * level;

    bool touchesWall(Level *level);

    Vector2D Velocity;
    Vector2DAngle RotationAngle;
    Vector2D Position;

private:
};

#endif // SNAKE_H
