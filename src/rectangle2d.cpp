#include "rectangle2d.h"

Rectangle2D::Rectangle2D()
{
}

Rectangle2D::Rectangle2D(double x, double y, double w, double h) : _x(x), _y(y), _w(w), _h(h)
{
    this->_right = x + w;
    this->_bottom = y + h;
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
