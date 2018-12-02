#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>
#include <math.h>
#include "game_object.h"

class Camera
{
public:
    Camera();

    SDL_Rect frame;//the location and size of the camera inside the level

    void followGameObject(GameObject& gameObject, int levelWidth, int levelHeight);//Center the camera over the game object
};

#endif // CAMERA_H
