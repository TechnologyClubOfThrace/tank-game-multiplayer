#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "game.h"
#include "viewport.h"
#include "entity.h"
#include "point_collider2d.h"
#include "rectangle_collider2d.h"
#include "convex_polygon_collider2d.h"

class CollisionSystem
{
public:
    CollisionSystem();
    static void DetectAndRespond(const Entity &entity, const std::vector<std::unique_ptr<Entity>>::iterator in_it);

    static bool AreColliding(const std::unique_ptr<Collider2D> &checkerCollider, const std::unique_ptr<Collider2D> &otherCollider);
    static bool AreColliding(const ConvexPolygonCollider2D &convexCollider2d, const RectangleCollider2D &rectangleCollider2d);
    static bool AreColliding(const ConvexPolygonCollider2D &convexCollider2d_1, const ConvexPolygonCollider2D &convexCollider2d_2);
    static bool AreColliding(const ConvexPolygonCollider2D &convexCollider2d, const PointCollider2D &pointCollider2d);
    static bool AreColliding(const RectangleCollider2D &rectangleCollider2d_1, const RectangleCollider2D &rectangleCollider2d_2);
    static bool AreColliding(const RectangleCollider2D &rectangleCollider2d, const PointCollider2D &pointCollider2d);
    static bool AreColliding(const PointCollider2D &pointCollider2d_1, const PointCollider2D &pointCollider2d_2);
};

#endif // COLLISION_SYSTEM_H
