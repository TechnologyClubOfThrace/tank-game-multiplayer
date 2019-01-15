#ifndef POINT_COLLIDER2D_H
#define POINT_COLLIDER2D_H

#include "collider2d.h"
#include "vector2d.h"

class PointCollider2D : public Collider2D
{
public:
    PointCollider2D();
    PointCollider2D(Vector2D point);

    Vector2D point;
};

#endif // POINT_COLLIDER2D_H
