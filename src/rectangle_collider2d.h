/* ***********************************************************************
 * Tank Game Multiplayer
 * (C) 2018 by Yiannis     Bourkelis  (hello@andama.org)
 * (C) 2018 by Christos    Paraskevas (cparaskevas91@gmail.com)
 * (C) 2018 by Constantine Sarmidis
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

#ifndef RECTANGLE_COLLIDER2D_H
#define RECTANGLE_COLLIDER2D_H

#include "collider2d.h"
#include "rectangle2d.h"

class RectangleCollider2D : public Collider2D
{
public:
    RectangleCollider2D(const CollisionRespose collision_response);
    RectangleCollider2D(Rectangle2D rect, const CollisionRespose collision_response);

    Rectangle2D rectangle;
};

#endif // RECTANGLE_COLLIDER2D_H
