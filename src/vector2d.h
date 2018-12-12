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

#ifndef VECTOR2D_H
#define VECTOR2D_H


class Vector2D
{
public:
    Vector2D();
    Vector2D(double x, double y);

    double x = 0;
    double y = 0;

    //functions
    void Rotate(const double angle);
    void SetMagnitude(const double newMagnitudes);
    double Magnitude() const;

    //operators
    Vector2D& operator*= (const double scalar);
    Vector2D operator* (const double scalar) const;
    Vector2D& operator/= (const double scalar);
    Vector2D operator/ (const double scalar) const;
    Vector2D& operator+= (const double scalar);
    Vector2D operator+ (const double scalar) const;
    Vector2D& operator+= (const Vector2D &vector2d);
    Vector2D operator+ (const Vector2D &vector2d) const;

    //static functions
    static Vector2D Up();
    static Vector2D Down();
    static Vector2D Left();
    static Vector2D Right();
};

#endif // VECTOR2D_H
