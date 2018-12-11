#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <chrono>
#include "rigid_body2d_component.h"
#include "transform_component.h"
#include "tank_input_component.h"

class PhysicsSystem
{
public:
    PhysicsSystem();

    void Update(const std::chrono::milliseconds::rep &deltaTime,
                TransformComponent &transformComponent,
                const TankInputComponent &tankInputComponent,
                RigidBody2DComponent &rigidBody2dComponent);
};

#endif // PHYSICS_SYSTEM_H
