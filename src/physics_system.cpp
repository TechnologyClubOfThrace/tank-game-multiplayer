#include "physics_system.h"

PhysicsSystem::PhysicsSystem()
{

}

void PhysicsSystem::Update(const std::chrono::milliseconds::rep &deltaTime,
                           TransformComponent &transformComponent,
                           const TankInputComponent &tankInputComponent,
                           RigidBody2DComponent &rigidBody2dComponent)
{
    switch (tankInputComponent.state) {
    case State::moveForward:
        transformComponent.Position.x += deltaTime*0.05;
        break;
    case State::moveBackwards:
        transformComponent.Position.x -= deltaTime*0.05;
        break;
    }

}
