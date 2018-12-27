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

ViewPort::ViewPort()
{

}

ViewPort::~ViewPort()
{

}

void ViewPort::FollowEntity(TransformComponent &transformComponent, SpriteComponent &spriteComponent, double levelWidth, double levelHeight)
{
    //calculations do not need rounding because it causes the entity on camera to shake
    this->camera.frame.x = static_cast<int>(round((transformComponent.Position.x + static_cast<double>(spriteComponent.sourceRectangle.w) / 2.0 ) - (static_cast<double>(this->camera.frame.w) / 2.0)));
    this->camera.frame.y = static_cast<int>(((transformComponent.Position.y + static_cast<double>(spriteComponent.sourceRectangle.h) / 2.0 ) - (static_cast<double>(this->camera.frame.h) / 2.0)));

    //this->camera.frame.x = (transformComponent.Position.x + spriteComponent.sourceRectangle.w / 2.0 ) - (this->camera.frame.w / 2.0);
    //this->camera.frame.y = (transformComponent.Position.y + spriteComponent.sourceRectangle.h / 2.0 ) - (this->camera.frame.h / 2.0);

    //Keep the camera in bounds
    if( this->camera.frame.x < 0 )
    {
        this->camera.frame.x = 0;
    }
    if( this->camera.frame.y < 0 )
    {
        this->camera.frame.y = 0;
    }
    if( this->camera.frame.x > levelWidth - this->camera.frame.w )
    {
        this->camera.frame.x = levelWidth - this->camera.frame.w;
    }
    if( this->camera.frame.y > levelHeight - this->camera.frame.h )
    {
        this->camera.frame.y = levelHeight - this->camera.frame.h;
    }
}
