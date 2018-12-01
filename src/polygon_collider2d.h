#ifndef POLYGON_COLLIDER2D_H
#define POLYGON_COLLIDER2D_H

#include "collider2d.h"
#include <vector>
#include <vector2d.h>

class PolygonCollider2D : public Collider2D
{
public:
    PolygonCollider2D();

    std::vector<Vector2D> points;

    bool isTouching(Collider2D collider);
};

#endif // POLYGON_COLLIDER2D_H
