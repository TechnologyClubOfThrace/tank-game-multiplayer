#include "point_collider2d.h"

PointCollider2D::PointCollider2D(const CollisionRespose collision_response)
    : Collider2D (Collider2DType::PointCollider2D, collision_response), point {0,0}
{
}

PointCollider2D::PointCollider2D(Vector2D point, const CollisionRespose collision_response)
    : Collider2D (Collider2DType::PointCollider2D, collision_response), point{point}
{
}

bool PointCollider2D::operator==(const PointCollider2D &other) const
{
    return this->point == other.point;
}
