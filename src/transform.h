#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vector2d.h"
#include "vector2d_angle.h"

class Transform
{
public:
    Transform();

    Vector2D Position;
    Vector2D Scale;
    Vector2DAngle Rotation;

};

#endif // TRANSFORM_H
