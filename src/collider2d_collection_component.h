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

#ifndef COLLIDER2D_COLLECTION_COMPONENT_H
#define COLLIDER2D_COLLECTION_COMPONENT_H

#include <vector>
#include <memory>
#include "collider2d.h"

class Collider2DCollectionComponent
{
public:
    Collider2DCollectionComponent();

    std::vector<std::unique_ptr<Collider2D>> colliders;

    bool isCollisionChecker = false;
    bool allowsCollisionCheck = false;
};

#endif // COLLIDER2D_COLLECTION_COMPONENT_H
