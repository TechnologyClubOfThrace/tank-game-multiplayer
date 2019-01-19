#include "point_collider2d.h"

PointCollider2D::PointCollider2D() : Collider2D (Collider2DType::PointCollider2D), point {0,0}
{
}

PointCollider2D::PointCollider2D(Vector2D point) : Collider2D (Collider2DType::PointCollider2D), point {point}
{
}

bool PointCollider2D::operator==(const PointCollider2D &other) const
{
    return this->point == other.point;
}
