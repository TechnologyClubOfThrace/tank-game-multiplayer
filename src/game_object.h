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

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <chrono>
#include <memory>
#include <vector>
#include "vector2d.h"
#include "texture_wrapper.h"
#include "collider2d.h"

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void handleEvent(SDL_Event &e);
    virtual void Update(std::chrono::milliseconds::rep deltaTime);
    virtual void Draw();
    virtual void Draw(size_t viewportIndex);

    std::vector<std::unique_ptr<Collider2D>> colliders;

    Vector2D Position;
    TextureWrapper texture;

    bool Exists = true;
};

#endif // GAME_OBJECT_H
