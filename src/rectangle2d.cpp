#include "rectangle2d.h"

Rectangle2D::Rectangle2D()
{
}

Rectangle2D::Rectangle2D(SDL_Rect rect) : Rectangle2D(rect.x, rect.y, rect.w, rect.h)
{
    calculate_right_and_bottom();
}

Rectangle2D::Rectangle2D(double x, double y, double w, double h) : _x(x), _y(y), _w(w), _h(h)
{
    calculate_right_and_bottom();
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

void Rectangle2D::setXYWH(double x, double y, double w, double h)
{
    this->_x = x;
    this->_y = y;
    this->_w = w;
    this->_h = h;
    calculate_right_and_bottom();
}

void Rectangle2D::setXY(Vector2D &vector2d)
{
    setXY(vector2d.x, vector2d.y);
}

void Rectangle2D::setXY(double x, double y)
{
    this->_x = x;
    this->_y = y;
    calculate_right_and_bottom();
}

void Rectangle2D::setX(double x)
{
    this->_x = x;
    this->_right = this->_x + this->_w;
}

void Rectangle2D::setY(double y)
{
    this->_y = y;
    this->_bottom = this->_y + this->_h;
}

void Rectangle2D::calculate_right_and_bottom()
{
    this->_right = this->_x + this->_w;
    this->_bottom = this->_y + this->_h;
}
