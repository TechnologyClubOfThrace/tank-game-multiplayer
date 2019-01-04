/* ***********************************************************************
 * Tank Game Multiplayer
 * (C) 2018 by Yiannis     Bourkelis  (hello@andama.org)
 * (C) 2018 by Christos    Paraskevas (cparaskevas91@gmail.com)
 * (C) 2018 by Constantine Sarmidis   (hello@andama.org)
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

#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <memory>
#include <vector>
#include "vector2d.h"

class TransformComponent
{
public:
    TransformComponent();

    Vector2D Position {0,0};
    Vector2D Scale {1,1};
    double RotationAngleDegrees = 0;

    std::unique_ptr<std::vector<std::unique_ptr<TransformComponent>>> children = nullptr;
};

#endif // TRANSFORM_COMPONENT_H
