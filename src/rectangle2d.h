#ifndef RECTANGLE2D_H
#define RECTANGLE2D_H

#include <SDL.h>
#include "vector2d.h"

class Rectangle2D
{
public:
    Rectangle2D();
    Rectangle2D(SDL_Rect);
    Rectangle2D(double x, double y, double w, double h);

    double getX() const;
    double getY() const;
    double getW() const;
    double getH() const;
    double getRight() const;
    double getBottom() const;

    void setXY(Vector2D& vector2d);
private:
    double _x,_y,_w,_h;
    double _right, _bottom;

    void calculate_left_and_bottom();
};

#endif // RECTANGLE2D_H
