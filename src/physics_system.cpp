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

void PhysicsSystem::UpdateRotation(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent, TransformComponent &transformComponent)
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

void PhysicsSystem::UpdatePosition(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent)
{
    if(!rigidBody2dComponent.isAccelerationfrozen){
        rigidBody2dComponent.Velocity += rigidBody2dComponent.Acceleration * deltaTime;

        if(rigidBody2dComponent.Velocity.Magnitude() > rigidBody2dComponent.MaxVelocityMagnitude){
            rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.MaxVelocityMagnitude);
            rigidBody2dComponent.isAccelerationfrozen = true;
        }
    }
}

void PhysicsSystem::Update(const std::chrono::milliseconds::rep &deltaTime,
                           TransformComponent &transformComponent,
                           const TankInputComponent &tankInputComponent,
                           RigidBody2DComponent &rigidBody2dComponent)
{
    switch (tankInputComponent.state) {
    case State::stopped:
        break;

    case State::stoppedRotationClockwise:
        {
        UpdateRotation(deltaTime, rigidBody2dComponent, transformComponent);

        transformComponent.RotationAngleDegrees +=
                rigidBody2dComponent.AngularVelocityMagnitude * deltaTime +
                0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);
        }
        break;


    case State::stoppedRotationCounterClockwise:
        {
        UpdateRotation(deltaTime, rigidBody2dComponent, transformComponent);

        transformComponent.RotationAngleDegrees +=
                rigidBody2dComponent.AngularVelocityMagnitude * deltaTime -
                0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);
        }
        break;

    case State::moveForward:
    {
        UpdatePosition(deltaTime, rigidBody2dComponent);
        rigidBody2dComponent.Velocity.Rotate(transformComponent.RotationAngleDegrees * (M_PI / 180));
        transformComponent.Position += rigidBody2dComponent.Velocity * deltaTime;
    }
    break;

    case State::moveBackwards:
    {
        UpdatePosition(deltaTime, rigidBody2dComponent);
        rigidBody2dComponent.Velocity.Rotate(transformComponent.RotationAngleDegrees * M_PI / 180);

        transformComponent.Position -= rigidBody2dComponent.Velocity * deltaTime;
    }
    break;

    case State::forwardRotationClockwise:
    {
        //rotation
        UpdateRotation(deltaTime, rigidBody2dComponent, transformComponent);

        transformComponent.RotationAngleDegrees +=
                rigidBody2dComponent.AngularVelocityMagnitude * deltaTime +
                0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);

        //forward
        UpdatePosition(deltaTime, rigidBody2dComponent);
        rigidBody2dComponent.Velocity.Rotate(transformComponent.RotationAngleDegrees * M_PI / 180);

        transformComponent.Position += rigidBody2dComponent.Velocity * deltaTime;
        }
        break;

    case State::forwardRotationCounterClockwise:
    {
        //rotation
        double rotangtemp=transformComponent.RotationAngleDegrees;
        UpdateRotation(deltaTime, rigidBody2dComponent, transformComponent);

        transformComponent.RotationAngleDegrees +=
                rigidBody2dComponent.AngularVelocityMagnitude * deltaTime -
                0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);
        //forward
        UpdatePosition(deltaTime, rigidBody2dComponent);
        rigidBody2dComponent.Velocity.Rotate((transformComponent.RotationAngleDegrees-rotangtemp) * M_PI / 180);

        transformComponent.Position += rigidBody2dComponent.Velocity * deltaTime;
        }
        break;

    case State::backwardsRotationClockwise:
    {
        //rotation
        UpdateRotation(deltaTime, rigidBody2dComponent, transformComponent);

        transformComponent.RotationAngleDegrees +=
                rigidBody2dComponent.AngularVelocityMagnitude * deltaTime +
                0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);

        //forward
        UpdatePosition(deltaTime, rigidBody2dComponent);
        rigidBody2dComponent.Velocity.Rotate(transformComponent.RotationAngleDegrees * M_PI / 180);
        transformComponent.Position -= rigidBody2dComponent.Velocity * deltaTime;
        }
        break;

    case State::backwardsRotationCounterClockwise:
    {
        //rotation
        UpdateRotation(deltaTime, rigidBody2dComponent, transformComponent);

        transformComponent.RotationAngleDegrees +=
                rigidBody2dComponent.AngularVelocityMagnitude * deltaTime -
                0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);

        //forward
        UpdatePosition(deltaTime, rigidBody2dComponent);
        rigidBody2dComponent.Velocity.Rotate(transformComponent.RotationAngleDegrees * M_PI / 180);
        transformComponent.Position -= rigidBody2dComponent.Velocity * deltaTime;
        }
        break;

    }//switch
}
