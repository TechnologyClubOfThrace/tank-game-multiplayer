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

#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>
#include <math.h>
#include "game_object.h"
#include "transform_component.h"
#include "sprite_component.h"

class Camera
{
public:
    Camera();

    SDL_Rect frame;//the location and size of the camera inside the level

    void followGameObject(GameObject& gameObject, int levelWidth, int levelHeight);//Center the camera over the game object
    void followEntityObject(TransformComponent &transformComponent, SpriteComponent &spriteComponent, int levelWidth, int levelHeight);
};

#endif // CAMERA_H
