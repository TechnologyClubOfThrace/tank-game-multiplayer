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
#include <cmath>


PhysicsSystem::PhysicsSystem()
{

}


/*
Torque MUST take positive and negative values in order to rotate clockwise or counterclockwise respectively AND
increase /decrease the angular velocity
*/

void PhysicsSystem::UpdateAngularAcceleration (RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.AngularAccelerationMagnitude = rigidBody2dComponent.TorqueMagnitude / rigidBody2dComponent.MoI;
}

void PhysicsSystem::UpdateAngularVelocity(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent)
{
       if(!rigidBody2dComponent.isAngularAccelerationfrozen){
        rigidBody2dComponent.AngularVelocityMagnitude += rigidBody2dComponent.AngularAccelerationMagnitude * deltaTime;

        if(rigidBody2dComponent.AngularVelocityMagnitude > rigidBody2dComponent.AngularVelocityMaximumMagnitude){
            rigidBody2dComponent.AngularVelocityMagnitude = rigidBody2dComponent.AngularVelocityMaximumMagnitude;
            rigidBody2dComponent.isAngularAccelerationfrozen = true;
        }
    }
}


void PhysicsSystem::UpdateDeltaRotationDegrees(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.deltaRotationAngleeDegrees = rigidBody2dComponent.AngularVelocityMagnitude * deltaTime +
    0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * std::pow(deltaTime, 2);

   }


// UpdateForce rotates the Force vector and maintains the same length

void PhysicsSystem::UpdateForce(RigidBody2DComponent &rigidBody2dComponent)
{
   rigidBody2dComponent.Force.RotateDegrees(rigidBody2dComponent.deltaRotationAngleeDegrees);
}

void PhysicsSystem::UpdateAcceleration(RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.Acceleration = rigidBody2dComponent.Force / rigidBody2dComponent.Mass;
}

//this function updates the velocity magnitude ONLY. Velocity needs rotation just like the Force() does!!!
void PhysicsSystem::UpdateVelocity(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent)
{    
    if(!rigidBody2dComponent.isAccelerationfrozen){
         rigidBody2dComponent.Velocity += rigidBody2dComponent.Acceleration * static_cast<double>(deltaTime);

        if(rigidBody2dComponent.Velocity.Magnitude() > rigidBody2dComponent.VelocityMaximumMagnitude){
            //std::cout << "will call rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.MaxVelocityMagnitude)" << std::endl;
            rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.VelocityMaximumMagnitude);
            rigidBody2dComponent.isAccelerationfrozen = true;


        }


    }

}


void PhysicsSystem::UpdateVelocityDegrees(RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.Velocity.RotateDegrees(rigidBody2dComponent.deltaRotationAngleeDegrees);

}

void PhysicsSystem::UpdatePosition(const std::chrono::milliseconds::rep &deltaTime, RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.Position += rigidBody2dComponent.Velocity * deltaTime;
}


void PhysicsSystem::Update(const std::chrono::milliseconds::rep &deltaTime,
                           TransformComponent &transformComponent,
                           RigidBody2DComponent &rigidBody2dComponent)
{
    UpdateAngularAcceleration (rigidBody2dComponent);
    UpdateAngularVelocity(deltaTime,rigidBody2dComponent);
    UpdateDeltaRotationDegrees(deltaTime,rigidBody2dComponent);
    UpdateForce(rigidBody2dComponent);
    UpdateAcceleration(rigidBody2dComponent);
    UpdateVelocity(deltaTime,rigidBody2dComponent);
    UpdateVelocityDegrees(rigidBody2dComponent);


    UpdatePosition(deltaTime,rigidBody2dComponent);

    transformComponent.Position = rigidBody2dComponent.Position;
    transformComponent.RotationAngleDegrees += rigidBody2dComponent.deltaRotationAngleeDegrees;
    rigidBody2dComponent.RotationAngleDegrees = transformComponent.RotationAngleDegrees;


}
