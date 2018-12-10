#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "component.h"
#include "vector2d.h"

class TransformComponent : Component
{
public:
    TransformComponent();

    Vector2D Position;
    Vector2D Scale;
    double RotationAngle;
};

#endif // TRANSFORM_COMPONENT_H
