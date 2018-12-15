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

void PhysicsSystem::UpdateVelocity(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent)
{    
    if(!rigidBody2dComponent.isAccelerationfrozen){
        rigidBody2dComponent.Velocity += rigidBody2dComponent.Acceleration * static_cast<double>(deltaTime);

        if(rigidBody2dComponent.Velocity.Magnitude() > rigidBody2dComponent.MaxVelocityMagnitude){
            std::cout << "will call rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.MaxVelocityMagnitude)" << std::endl;
            rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.MaxVelocityMagnitude);
            rigidBody2dComponent.isAccelerationfrozen = true;
        }
    }else if(rigidBody2dComponent.isAngularAccelerationfrozen){
        rigidBody2dComponent.Velocity.Rotate(rigidBody2dComponent.deltaRotationAngleeDegrees * M_PI / 180);
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
        UpdateAngularVelocity(deltaTime, rigidBody2dComponent);

        rigidBody2dComponent.deltaRotationAngleeDegrees =
                rigidBody2dComponent.AngularVelocityMagnitude * deltaTime +
                0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);
        transformComponent.RotationAngleDegrees += rigidBody2dComponent.deltaRotationAngleeDegrees;
        rigidBody2dComponent.Force.Rotate(rigidBody2dComponent.deltaRotationAngleeDegrees * M_PI / 180);
        rigidBody2dComponent.Acceleration = rigidBody2dComponent.Force /rigidBody2dComponent.Mass;
        }
        break;


    case State::stoppedRotationCounterClockwise:
        {
        UpdateAngularVelocity(deltaTime, rigidBody2dComponent);

        rigidBody2dComponent.deltaRotationAngleeDegrees =
                rigidBody2dComponent.AngularVelocityMagnitude * deltaTime -
                0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);
        transformComponent.RotationAngleDegrees += rigidBody2dComponent.deltaRotationAngleeDegrees;
        rigidBody2dComponent.Force.Rotate(rigidBody2dComponent.deltaRotationAngleeDegrees* M_PI / 180);
        rigidBody2dComponent.Acceleration = rigidBody2dComponent.Force /rigidBody2dComponent.Mass;
        }
        break;

    case State::moveForward:
    {
        UpdateVelocity(deltaTime, rigidBody2dComponent);

        transformComponent.Position += rigidBody2dComponent.Velocity * deltaTime;
        std::cout << "x: " << transformComponent.Position.x << ", y: " << transformComponent.Position.y << std::endl;
        std::cout << "velocity x: " << rigidBody2dComponent.Velocity.x << ", velocity y: " << rigidBody2dComponent.Velocity.y << std::endl;
    }
    break;

    case State::moveBackwards:
    {
        UpdateVelocity(deltaTime, rigidBody2dComponent);

        transformComponent.Position -= rigidBody2dComponent.Velocity * deltaTime;
    }
    break;

    case State::forwardRotationClockwise:
    {
        //rotation
        UpdateAngularVelocity(deltaTime, rigidBody2dComponent);

        rigidBody2dComponent.deltaRotationAngleeDegrees =
                rigidBody2dComponent.AngularVelocityMagnitude * deltaTime +
                0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);
        transformComponent.RotationAngleDegrees += rigidBody2dComponent.deltaRotationAngleeDegrees;
        rigidBody2dComponent.Force.Rotate(rigidBody2dComponent.deltaRotationAngleeDegrees * M_PI / 180);
        rigidBody2dComponent.Acceleration = rigidBody2dComponent.Force /rigidBody2dComponent.Mass;
        //rigidBody2dComponent.Velocity.Rotate(rigidBody2dComponent.deltaRotationAngleeDegrees * M_PI / 180);

        //forward
        UpdateVelocity(deltaTime, rigidBody2dComponent);

        transformComponent.Position += rigidBody2dComponent.Velocity * deltaTime;
        }
        break;

    case State::forwardRotationCounterClockwise:
    {
        //rotation
        UpdateAngularVelocity(deltaTime, rigidBody2dComponent);

        rigidBody2dComponent.deltaRotationAngleeDegrees =
                rigidBody2dComponent.AngularVelocityMagnitude * deltaTime -
                0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);
        transformComponent.RotationAngleDegrees += rigidBody2dComponent.deltaRotationAngleeDegrees;
        rigidBody2dComponent.Force.Rotate(rigidBody2dComponent.deltaRotationAngleeDegrees * M_PI / 180);
        rigidBody2dComponent.Acceleration = rigidBody2dComponent.Force /rigidBody2dComponent.Mass;

        //forward
        UpdateVelocity(deltaTime, rigidBody2dComponent);

        transformComponent.Position += rigidBody2dComponent.Velocity * deltaTime;
        }
        break;

    case State::backwardsRotationClockwise:
    {
        //rotation
        UpdateAngularVelocity(deltaTime, rigidBody2dComponent);

        rigidBody2dComponent.deltaRotationAngleeDegrees =
                rigidBody2dComponent.AngularVelocityMagnitude * deltaTime +
                0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);
        transformComponent.RotationAngleDegrees += rigidBody2dComponent.deltaRotationAngleeDegrees;
        rigidBody2dComponent.Force.Rotate(rigidBody2dComponent.deltaRotationAngleeDegrees * M_PI / 180);
        rigidBody2dComponent.Acceleration = rigidBody2dComponent.Force /rigidBody2dComponent.Mass;

        //forward
        UpdateVelocity(deltaTime, rigidBody2dComponent);

        transformComponent.Position -= rigidBody2dComponent.Velocity * deltaTime;
        }
        break;

    case State::backwardsRotationCounterClockwise:
    {
        //rotation
        UpdateAngularVelocity(deltaTime, rigidBody2dComponent);

        rigidBody2dComponent.deltaRotationAngleeDegrees =
                rigidBody2dComponent.AngularVelocityMagnitude * deltaTime -
                0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);
        transformComponent.RotationAngleDegrees += rigidBody2dComponent.deltaRotationAngleeDegrees;
        rigidBody2dComponent.Force.Rotate(rigidBody2dComponent.deltaRotationAngleeDegrees * M_PI / 180);
        rigidBody2dComponent.Acceleration = rigidBody2dComponent.Force /rigidBody2dComponent.Mass;
        //forward
        UpdateVelocity(deltaTime, rigidBody2dComponent);

        transformComponent.Position -= rigidBody2dComponent.Velocity * deltaTime;
        }
        break;

    }//switch
}
