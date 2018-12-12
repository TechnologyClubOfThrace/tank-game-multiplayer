/* ***********************************************************************
 * Tank Game Multiplayer
 * (C) 2018 by Yiannis     Bourkelis  (hello@andama.org)
 * (C) 2018 by Christos    Paraskevas (cparaskevas91@gmail.com)
 * (C) 2018 by Constantine Sarmidis   (hello@andama.org)
 *
 * This file is part of Tank Game Multiplayer.
 *
 * Tank Game Multiplayer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank Game Multiplayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tank Game Multiplayer.  If not, see <http://www.gnu.org/licenses/>.
 * ***********************************************************************/

#include "vector2d.h"
#include <math.h>

Vector2D::Vector2D()
{
}

Vector2D::Vector2D(double x, double y) : x(x), y(y)
{
}

//-----------------------------------------------------------------------------
// Purpose: Rotate a vector
//-----------------------------------------------------------------------------
void Vector2D::Rotate( const double angle )
{
    double xt = (x * cos(angle)) - (y * sin(angle));
    double yt = (y * cos(angle)) + (x * sin(angle));

    x = xt;
    y = yt;
}

void Vector2D::SetMagnitude(const double newMagnitudes)
{
    double mag = this->Magnitude();
    this->x = this->x * newMagnitudes / mag;
    this->y = this->y * newMagnitudes / mag;
}

double Vector2D::Magnitude() const
{
    return sqrt(x * x + y * y);
}

Vector2D& Vector2D::operator*=(const double scalar)
{
    this->x *= scalar;
    this->y *= scalar;

    return *this;
}

Vector2D Vector2D::operator*(const double scalar) const
{
    Vector2D out;
    out.x = this->x * scalar;
    out.y = this->y * scalar;
    return out;
}

Vector2D& Vector2D::operator/=(const double scalar)
{
    this->x /= scalar;
    this->y /= scalar;

    return *this;
}


Vector2D Vector2D::operator/(const double scalar) const
{
    Vector2D out;
    out.x = this->x / scalar;
    out.y = this->y / scalar;
    return out;
}


Vector2D& Vector2D::operator+=(const double scalar)
{
    this->x += scalar;
    this->y += scalar;

    return *this;
}

Vector2D Vector2D::operator+(const double scalar) const
{
    Vector2D out;
    out.x = this->x + scalar;
    out.y = this->y + scalar;

    return out;
}

Vector2D& Vector2D::operator+=(const Vector2D &vector2d)
{
    this->x += vector2d.x;
    this->y += vector2d.y;

    return *this;
}

Vector2D Vector2D::operator+(const Vector2D &vector2d) const
{
    Vector2D out;
    out.x = this->x + vector2d.x;
    out.y = this->y + vector2d.y;

    return out;
}

Vector2D& Vector2D::operator-=(const Vector2D &vector2d)
{
    this->x -= vector2d.x;
    this->y -= vector2d.y;

    return *this;
}

Vector2D Vector2D::Up()
{
    return Vector2D(0, -1);
}

Vector2D Vector2D::Down()
{
    return Vector2D(0, 1);
}

Vector2D Vector2D::Left()
{
    return Vector2D(-1, 0);
}

Vector2D Vector2D::Right()
{
    return Vector2D(1, 0);
}
