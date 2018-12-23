/* ***********************************************************************
 * Tank Game Multiplayer
 * (C) 2018 by Yiannis     Bourkelis  (hello@andama.org)
 * (C) 2018 by Christos    Paraskevas (cparaskevas91@gmail.com)
 * (C) 2018 by Constantine Sarmidis   (hello@andama.org)
 *
 * This file is part of Tank Game Multiplayer.
 *
 * Tank Game Multiplayer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank Game Multiplayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tank Game Multiplayer.  If not, see <http://www.gnu.org/licenses/>.
 * ***********************************************************************/


#include "physics_system.h"


PhysicsSystem::PhysicsSystem()
{

}

void PhysicsSystem::UpdateAngularVelocity(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.AngularAccelerationMagnitude = rigidBody2dComponent.TorqueMagnitude / rigidBody2dComponent.MoI;

    if(!rigidBody2dComponent.isAngularAccelerationfrozen){
        rigidBody2dComponent.AngularVelocityMagnitude += rigidBody2dComponent.AngularAccelerationMagnitude * deltaTime;

        if(rigidBody2dComponent.AngularVelocityMagnitude > rigidBody2dComponent.AngularVelocityMaximumMagnitude){
            rigidBody2dComponent.AngularVelocityMagnitude = rigidBody2dComponent.AngularVelocityMaximumMagnitude;
            rigidBody2dComponent.isAngularAccelerationfrozen = true;
        }
    }
}

void PhysicsSystem::UpdateForce(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent, TransformComponent &transformComponent)
{
    rigidBody2dComponent.Force = rigidBody2dComponent.DirectionalForce;
    rigidBody2dComponent.Force.RotateDegrees(transformComponent.RotationAngleDegrees);
}

void PhysicsSystem::UpdateAcceleration(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.Acceleration = rigidBody2dComponent.Force / rigidBody2dComponent.Mass;
}

void PhysicsSystem::UpdateRotationDegreesClockwise(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent, TransformComponent &transformComponent)
{
    rigidBody2dComponent.deltaRotationAngleeDegrees = rigidBody2dComponent.AngularVelocityMagnitude * deltaTime +
    0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);
    transformComponent.RotationAngleDegrees += rigidBody2dComponent.deltaRotationAngleeDegrees;
    //std::cout << rigidBody2dComponent.deltaRotationAngleeDegrees << std::endl;
}

void PhysicsSystem::UpdateRotationDegreesCounterClockwise(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent, TransformComponent &transformComponent)
{
    rigidBody2dComponent.deltaRotationAngleeDegrees = -rigidBody2dComponent.AngularVelocityMagnitude * deltaTime -
    0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);
    transformComponent.RotationAngleDegrees += rigidBody2dComponent.deltaRotationAngleeDegrees;
    //std::cout << rigidBody2dComponent.deltaRotationAngleeDegrees << std::endl;
}

void PhysicsSystem::UpdateVelocity(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent, const TankInputComponent &tankInputComponent)
{    
    if(!rigidBody2dComponent.isAccelerationfrozen){
        rigidBody2dComponent.Velocity.RotateDegrees(rigidBody2dComponent.deltaRotationAngleeDegrees);
        rigidBody2dComponent.Velocity += rigidBody2dComponent.Acceleration * static_cast<double>(deltaTime);

        if(rigidBody2dComponent.Velocity.Magnitude() > rigidBody2dComponent.MaxVelocityMagnitude){
            //std::cout << "will call rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.MaxVelocityMagnitude)" << std::endl;
            rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.MaxVelocityMagnitude);
            rigidBody2dComponent.isAccelerationfrozen = true;
        }
    } else if(rigidBody2dComponent.isAngularAccelerationfrozen){
        if ( (tankInputComponent.state == State::forwardRotationClockwise) ||
            (tankInputComponent.state == State::forwardRotationCounterClockwise) ||
            (tankInputComponent.state == State::backwardsRotationClockwise) ||
            (tankInputComponent.state == State::backwardsRotationCounterClockwise)) {
            rigidBody2dComponent.Velocity.RotateDegrees(rigidBody2dComponent.deltaRotationAngleeDegrees);
        }
    }

}

void PhysicsSystem::UpdatePositionForward(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent, TransformComponent &transformComponent)
{
    transformComponent.Position += rigidBody2dComponent.Velocity * deltaTime;
}

void PhysicsSystem::UpdatePositionBackwards(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent, TransformComponent &transformComponent)
{
    transformComponent.Position -= rigidBody2dComponent.Velocity * deltaTime;
}

void PhysicsSystem::Update(const std::chrono::milliseconds::rep &deltaTime,
                           TransformComponent &transformComponent,
                           const TankInputComponent &tankInputComponent,
                           RigidBody2DComponent &rigidBody2dComponent)
{
    switch (tankInputComponent.state) {

    case State::forward:
        UpdateVelocity(deltaTime, rigidBody2dComponent, tankInputComponent);
        UpdatePositionForward(deltaTime, rigidBody2dComponent, transformComponent);


        break;

    case State::forwardRotationClockwise:
        UpdateRotationDegreesClockwise(deltaTime, rigidBody2dComponent, transformComponent);
        UpdateAngularVelocity(deltaTime, rigidBody2dComponent);
        UpdateForce(deltaTime, rigidBody2dComponent, transformComponent);
        UpdateAcceleration(deltaTime, rigidBody2dComponent);
        UpdateVelocity(deltaTime, rigidBody2dComponent, tankInputComponent);
        UpdatePositionForward(deltaTime, rigidBody2dComponent, transformComponent);
        break;

    case State::forwardRotationCounterClockwise:
        UpdateRotationDegreesCounterClockwise(deltaTime, rigidBody2dComponent, transformComponent);
        UpdateAngularVelocity(deltaTime, rigidBody2dComponent);
        UpdateForce(deltaTime, rigidBody2dComponent, transformComponent);
        UpdateAcceleration(deltaTime, rigidBody2dComponent);
        UpdateVelocity(deltaTime, rigidBody2dComponent, tankInputComponent);
        UpdatePositionForward(deltaTime, rigidBody2dComponent, transformComponent);
        break;

    case State::backwardsRotationCounterClockwise:
        UpdateRotationDegreesCounterClockwise(deltaTime, rigidBody2dComponent, transformComponent);
        UpdateAngularVelocity(deltaTime, rigidBody2dComponent);
        UpdateForce(deltaTime, rigidBody2dComponent, transformComponent);
        UpdateAcceleration(deltaTime, rigidBody2dComponent);
        UpdateVelocity(deltaTime, rigidBody2dComponent, tankInputComponent);
        UpdatePositionBackwards(deltaTime, rigidBody2dComponent, transformComponent);
        break;

    case State::backwardsRotationClockwise:
        UpdateRotationDegreesClockwise(deltaTime, rigidBody2dComponent, transformComponent);
        UpdateAngularVelocity(deltaTime, rigidBody2dComponent);
        UpdateForce(deltaTime, rigidBody2dComponent, transformComponent);
        UpdateAcceleration(deltaTime, rigidBody2dComponent);
        UpdateVelocity(deltaTime, rigidBody2dComponent, tankInputComponent);
        UpdatePositionBackwards(deltaTime, rigidBody2dComponent, transformComponent);
        break;

    case State::backwards:
        UpdateVelocity(deltaTime, rigidBody2dComponent, tankInputComponent);
        UpdatePositionBackwards(deltaTime, rigidBody2dComponent, transformComponent);
        break;

    case State::stoppedRotationClockwise:
        UpdateAngularVelocity(deltaTime, rigidBody2dComponent);
        UpdateRotationDegreesClockwise(deltaTime, rigidBody2dComponent, transformComponent);
        break;

    case State::stoppedRotationCounterClockwise:
        UpdateAngularVelocity(deltaTime, rigidBody2dComponent);
        UpdateRotationDegreesCounterClockwise(deltaTime, rigidBody2dComponent, transformComponent);
        break;

    case State::stopped:
        break;

    }//switch
}
