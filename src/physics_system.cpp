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
    {
        //transformComponent.Position.x += deltaTime*0.05;
        Vector2D acceleration (0.000025,0); //= rigidBody2dComponent.Force / rigidBody2dComponent.Mass;
        //double deltaSeconds =  static_cast<double>(deltaTime) / 1000;
        if (rigidBody2dComponent.Velocity.Magnitude() < 0.10){
            rigidBody2dComponent.Velocity += acceleration * static_cast<double>(deltaTime);
        }
        transformComponent.Position += rigidBody2dComponent.Velocity * static_cast<double>(deltaTime);
        //rigidBody2dComponent.Velocity
Vector2D tade2 = acceleration *  1000;
    }
        break;
    case State::moveBackwards:
        transformComponent.Position.x -= deltaTime*0.05;
        break;
    }

}
