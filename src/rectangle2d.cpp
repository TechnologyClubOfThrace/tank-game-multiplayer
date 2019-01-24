#include "rectangle2d.h"

Rectangle2D::Rectangle2D()
{
}

Rectangle2D::Rectangle2D(SDL_Rect rect) : Rectangle2D(rect.x, rect.y, rect.w, rect.h)
{
}

Rectangle2D::Rectangle2D(double x, double y, double w, double h) : _x(x), _y(y), _w(w), _h(h)
{
    calculate_left_and_bottom();
}

double Rectangle2D::getX() const
{
    return this->_x;
}
double Rectangle2D::getY() const
{
    return this->_y;
}
double Rectangle2D::getW() const
{
    return this->_w;
}
double Rectangle2D::getH() const
{
    return this->_h;
}

double Rectangle2D::getRight() const
{
    return this->_right;
}
double Rectangle2D::getBottom() const
{
    return this->_bottom;
}

void Rectangle2D::setXY(Vector2D &vector2d)
{
    this->_x = vector2d.x;
    this->_y = vector2d.y;
    calculate_left_and_bottom();
}

void Rectangle2D::calculate_left_and_bottom()
{
    this->_right = this->_x + this->_w;
    this->_bottom = this->_y + this->_h;
}
