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

void PhysicsSystem::UpdateAngularAcceleration (const Entity& entity)
{
    entity.rigid_body2d_component->AngularAccelerationMagnitude = entity.rigid_body2d_component->TorqueMagnitude / entity.rigid_body2d_component->MoI;
}

void PhysicsSystem::UpdateAngularVelocity(const std::chrono::milliseconds::rep &deltaTime, const Entity& entity)
{
       if(!entity.rigid_body2d_component->isAngularAccelerationfrozen){
        entity.rigid_body2d_component->AngularVelocityMagnitude += entity.rigid_body2d_component->AngularAccelerationMagnitude * deltaTime;

        if(entity.rigid_body2d_component->AngularVelocityMagnitude > entity.rigid_body2d_component->AngularVelocityMaximumMagnitude){
            entity.rigid_body2d_component->AngularVelocityMagnitude = entity.rigid_body2d_component->AngularVelocityMaximumMagnitude;
            entity.rigid_body2d_component->isAngularAccelerationfrozen = true;
        }
    }
}


void PhysicsSystem::UpdateDeltaRotationDegrees(const std::chrono::milliseconds::rep &deltaTime, const Entity& entity)
{
    entity.rigid_body2d_component->deltaRotationAngleeDegrees = entity.rigid_body2d_component->AngularVelocityMagnitude * deltaTime +
    0.5 * entity.rigid_body2d_component->AngularAccelerationMagnitude * std::pow(deltaTime, 2);

   }


// UpdateForce rotates the Force vector and maintains the same length

void PhysicsSystem::UpdateForce(const Entity& entity)
{
   entity.rigid_body2d_component->Force.RotateDegrees(entity.rigid_body2d_component->deltaRotationAngleeDegrees);
}

void PhysicsSystem::UpdateAcceleration(const Entity& entity)
{
    entity.rigid_body2d_component->Acceleration = entity.rigid_body2d_component->Force / entity.rigid_body2d_component->Mass;
}

//this function updates the velocity magnitude ONLY. Velocity needs rotation just like the Force() does!!!
void PhysicsSystem::UpdateVelocity(const std::chrono::milliseconds::rep &deltaTime, const Entity& entity)
{    
    if(!entity.rigid_body2d_component->isAccelerationfrozen){

         entity.rigid_body2d_component->Velocity += entity.rigid_body2d_component->Acceleration * static_cast<double>(deltaTime);


        if(entity.rigid_body2d_component->Velocity.Magnitude() > entity.rigid_body2d_component->VelocityMaximumMagnitude){
            //std::cout << "will call rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.MaxVelocityMagnitude)" << std::endl;
            entity.rigid_body2d_component->Velocity.SetMagnitude(entity.rigid_body2d_component->VelocityMaximumMagnitude);
            entity.rigid_body2d_component->isAccelerationfrozen = true;
        }
    }
}


void PhysicsSystem::UpdateVelocityDegrees(const Entity& entity)
{
    entity.rigid_body2d_component->Velocity.RotateDegrees(entity.rigid_body2d_component->deltaRotationAngleeDegrees);
}

void PhysicsSystem::UpdatePosition(const std::chrono::milliseconds::rep &deltaTime, const Entity& entity)
{
    entity.rigid_body2d_component->Position += entity.rigid_body2d_component->Velocity * deltaTime;
}


void PhysicsSystem::Update(const std::chrono::milliseconds::rep &deltaTime, const Entity& entity, const std::vector<std::unique_ptr<Entity>>::iterator in_it)
{
    //store current position, rotation and rigidbody in case there is a collision to roll back the values
    static TransformComponent prevTransform;
    static RigidBody2DComponent prevRigidbody;
    prevTransform = *entity.transform_component;
    prevRigidbody = *entity.rigid_body2d_component;

    //apply physics to the entity's rigidbody
    UpdateAngularAcceleration (entity);
    UpdateAngularVelocity(deltaTime, entity);
    UpdateDeltaRotationDegrees(deltaTime, entity);
    UpdateForce(entity);
    UpdateAcceleration(entity);
    UpdateVelocity(deltaTime, entity);
    UpdateVelocityDegrees(entity);
    UpdatePosition(deltaTime, entity);

    //update entity's transform and rigidbody
    entity.transform_component->Position = entity.rigid_body2d_component->Position;
    entity.transform_component->RotationAngleDegrees += entity.rigid_body2d_component->deltaRotationAngleeDegrees;
    entity.rigid_body2d_component->RotationAngleDegrees = entity.transform_component->RotationAngleDegrees;

    //check collisions
    if (entity.collider2d_collection_component && entity.collider2d_collection_component->isCollisionChecker){
        auto collisionResult = CollisionSystem::DetectAndRespond(entity, in_it);

        //check collision result
        if (collisionResult == CollisionSystemResult::RevertTransform){
            *entity.transform_component = prevTransform;
            *entity.rigid_body2d_component = prevRigidbody;
        }
    }
}
