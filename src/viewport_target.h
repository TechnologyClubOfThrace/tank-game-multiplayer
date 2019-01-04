#ifndef VIEWPORT_TARGET_H
#define VIEWPORT_TARGET_H

#include <cstring>
#include <SDL.h>
#include "vector2d.h"

class ViewportTarget
{
public:
    ViewportTarget() = delete;
    ViewportTarget(size_t viewportID);
    Vector2D EntityScale {1,1};
    bool movesTheCamera = false;
    size_t viewportID {};//the vieport id where the related entity sprite will be drawn
    //Vector2D entityScale {1, 1};//the scale at whitch the entity sprite will be rendered inside the viewport
    SDL_Rect destinationRectangle {};//the desired position and size of the rendered sprite. x and y is calculated inside render system
};

#endif // VIEWPORT_TARGET_H
