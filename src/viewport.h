#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <SDL.h>
#include "camera.h"

class ViewPort
{
public:
    ViewPort();

    SDL_Rect frame;//the location of the viewport
    Camera camera;//the camera of the viewport
};

#endif // VIEWPORT_H
