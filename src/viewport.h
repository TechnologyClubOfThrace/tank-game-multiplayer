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

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <SDL.h>
#include <memory>
#include <vector>
#include "camera.h"
#include "sprite_component.h"
#include "transform_component.h"

class ViewPort
{
public:
    ViewPort();
    ~ViewPort();

    //member variables
    SDL_Rect frame;//the location of the viewport
    size_t cameraID = 0;//the related camera index inside the camera array
    Vector2D entityScale {1, 1};//the scale at which the entity sprite will be rendered inside the viewport. background_sprite_component is not affected
    std::shared_ptr<SpriteComponent> background_sprite_component = nullptr;//the background sprite of the viewport   todo: why cant i use a unique_ptr here;

    static std::vector<Camera> allCameras;

    //Screen dimensions
    static int ScreenWidth;
    static int ScreenHeight;

    //Level dimensions
    static double levelWidth;
    static double levelHeight;

    //methods
    static void FollowEntity(const TransformComponent &transformComponent, const SpriteComponent &spriteComponent, const ViewPort &viewport); //Center the camera over the game object
};

#endif // VIEWPORT_H
