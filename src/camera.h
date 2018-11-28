#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>

class Camera
{
public:
    Camera();

    SDL_Rect frame;//the location and size of the camera inside the level
};

#endif // CAMERA_H
