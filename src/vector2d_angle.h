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

#ifndef VECTOR2D_ANGLE_H
#define VECTOR2D_ANGLE_H

#include "vector2d.h"
#include <vector>
#include <SDL.h>
#include <chrono>

enum class AngleDirection{
    None,
    Up,
    Down,
    Left,
    Right,
    Forward,
    Backward
};

class Vector2DAngle : public Vector2D
{

public:
    Vector2DAngle();

    double AngleRadiansPerMilliSec;//init from the constructor

    void AddAngleDirection(AngleDirection angleDirection);
    void RemoveAngleDirection(AngleDirection angleDirection);
    void Apply(Vector2D &velocity_vector, std::chrono::milliseconds::rep deltaTime);
    double CurrentAngleDegrees = 0;
    double ignoreValue = 0.0025;

    std::vector<AngleDirection> angle_directions;

private:
    AngleDirection mCurrentAngleDirection;
};

#endif // VECTOR2D_ANGLE_H
