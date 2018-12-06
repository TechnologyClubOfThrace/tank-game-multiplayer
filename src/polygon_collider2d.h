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

#ifndef POLYGON_COLLIDER2D_H
#define POLYGON_COLLIDER2D_H

#include "collider2d.h"
#include <vector>
#include <vector2d.h>

class PolygonCollider2D : public Collider2D
{
public:
    PolygonCollider2D();

    std::vector<Vector2D> points;

    bool isTouching(Collider2D collider);
};

#endif // POLYGON_COLLIDER2D_H
