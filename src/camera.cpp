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
        this->frame.x = static_cast<int>(round((gameObject.Position.x + gameObject.texture.getWidth() / 2 ) - (this->frame.w / 2)));
        this->frame.y = static_cast<int>(round(( gameObject.Position.y + gameObject.texture.getHeight() / 2 ) - (this->frame.h / 2)));

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
