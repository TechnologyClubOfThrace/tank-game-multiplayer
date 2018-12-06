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

#ifndef TANK_H
#define TANK_H

#include <SDL.h>
#include "texture_wrapper.h"
#include "level.h"
#include "vector2d.h"
#include "vector2d_angle.h"
#include "keystate.h"
#include "game_object.h"

enum class enumState
{
    stopped,
    stoppedFromForwards,
    stoppedFromBackwards,
    moveForward,
    moveBackwards
};

class Tank : public GameObject
{
public:
    Tank();
    void handleEvent(SDL_Event &e);
    void Draw();
    void Draw(size_t viewportIndex);
    void Update(std::chrono::milliseconds::rep deltaTime);

    void FireBullet();

    KeyState keystate;

    double NormalTankSpeed = 0.13;
    double FastTankSpeedMultiplier = 2.00;
    AngleDirection TankDirection = AngleDirection::Forward;
    AngleDirection TankDirectionBeforeStopping = AngleDirection::Forward;

    bool touchesWall(Level *level);

    Vector2D Velocity;
    Vector2D previousVelocity;

    Level * level;

private:
    enumState state = enumState::stopped;
    void setAngleDirection(SDL_Keysym& keysym);
};

#endif // TANK_H
