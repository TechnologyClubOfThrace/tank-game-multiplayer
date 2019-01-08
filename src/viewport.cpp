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

#include "viewport.h"

std::vector<Camera> ViewPort::allCameras;

//Screen dimensions
int ViewPort::ScreenWidth;
int ViewPort::ScreenHeight;

//Level dimensions
double ViewPort::levelWidth;
double ViewPort::levelHeight;

ViewPort::ViewPort()
{

}

ViewPort::~ViewPort()
{

}


void ViewPort::FollowEntity(const TransformComponent &transformComponent, const SpriteComponent &spriteComponent, const ViewPort& viewport)
{   
    //calculations do not need rounding because it causes the entity on camera to shake
    allCameras[viewport.cameraID].frame.x = static_cast<int>((transformComponent.Position.x * viewport.entityScale.x + (static_cast<double>(spriteComponent.sourceRectangle.w * viewport.entityScale.x) / 2.0) ) - (static_cast<double>(allCameras[viewport.cameraID].frame.w) / 2.0));
    allCameras[viewport.cameraID].frame.y = static_cast<int>((transformComponent.Position.y * viewport.entityScale.y + (static_cast<double>(spriteComponent.sourceRectangle.h * viewport.entityScale.y) / 2.0) ) - (static_cast<double>(allCameras[viewport.cameraID].frame.h) / 2.0));


    //Keep the camera in bounds
    if( allCameras[viewport.cameraID].frame.x < 0 )
    {
        allCameras[viewport.cameraID].frame.x = 0;
    }
    if( allCameras[viewport.cameraID].frame.y < 0 )
    {
        allCameras[viewport.cameraID].frame.y = 0;
    }
    if( allCameras[viewport.cameraID].frame.x > static_cast<int>(ViewPort::levelWidth * viewport.entityScale.x - allCameras[viewport.cameraID].frame.w))
    {
        allCameras[viewport.cameraID].frame.x = static_cast<int>(ViewPort::levelWidth * viewport.entityScale.x - allCameras[viewport.cameraID].frame.w);
    }
    if( allCameras[viewport.cameraID].frame.y > static_cast<int>(ViewPort::levelHeight * viewport.entityScale.y - allCameras[viewport.cameraID].frame.h))
    {
        allCameras[viewport.cameraID].frame.y = static_cast<int>(ViewPort::levelHeight * viewport.entityScale.y - allCameras[viewport.cameraID].frame.h);
    }
}

