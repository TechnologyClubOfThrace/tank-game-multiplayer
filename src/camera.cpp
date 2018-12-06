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

#include "camera.h"

/* viewport
 * split-screen effects
 * attach camera to player
 * glViewport
 * https://gamedev.stackexchange.com/questions/75991/camera-vs-viewport
 * room / scene / level
 */

Camera::Camera()
{

}

void Camera::followGameObject(GameObject &gameObject, int levelWidth, int levelHeight)
{
        this->frame.x = static_cast<int>(round((gameObject.transform.Position.x + gameObject.texture.getWidth() / 2 ) - (this->frame.w / 2)));
        this->frame.y = static_cast<int>(round(( gameObject.transform.Position.y + gameObject.texture.getHeight() / 2 ) - (this->frame.h / 2)));

        //Keep the camera in bounds
        if( this->frame.x < 0 )
        {
            this->frame.x = 0;
        }
        if( this->frame.y < 0 )
        {
            this->frame.y = 0;
        }
        if( this->frame.x > levelWidth - this->frame.w )
        {
            this->frame.x = levelWidth - this->frame.w;
        }
        if( this->frame.y > levelHeight - this->frame.h )
        {
            this->frame.y = levelHeight - this->frame.h;
        }
}
