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

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "game_object.h"
#include "viewport.h"

#include "entity.h"

class game
{
public:
    game();

    //vector of all game objects
    static std::vector<std::unique_ptr<GameObject>> gameObjects;
    static std::vector<std::unique_ptr<Entity>> entityObjects;

    //vector of any objects that should be added to the gameObjects vector
    //like bullets fired etc
    static std::vector<std::unique_ptr<GameObject>> gameObjects_for_addition;

    static std::vector<ViewPort> viewports;//the related viewports of the level. At least there should be one.
};

#endif // GAME_H
