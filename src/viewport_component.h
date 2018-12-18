#ifndef VIEWPORT_COMPONENT_H
#define VIEWPORT_COMPONENT_H

#include <cstring>
#include <SDL.h>
#include "vector2d.h"

class ViewportComponent
{
public:
    ViewportComponent();

    size_t viewportID {};//the vieport id where the related entity sprite will be drawn
    Vector2D entityScale {};//the scale at witch the entity sprite will be rendered inside the viewport
    SDL_Rect destinationRectangle {};//the desired position and size of the rendered sprite. x and y is calculated inside render system
};

#endif // VIEWPORT_COMPONENT_H
