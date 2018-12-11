#ifndef RIGID_BODY2D_COMPONENT_H
#define RIGID_BODY2D_COMPONENT_H

#include "vector2d.h"

class RigidBody2DComponent
{
public:
    RigidBody2DComponent();

    Vector2D Velocity{0,0};
};

#endif // RIGID_BODY_COMPONENT_H
