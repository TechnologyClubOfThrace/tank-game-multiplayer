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

#include "tank_input_system.h"
#include "render_utils.h"
#include "game.h"
//#include <math.h>

TankInputSystem::TankInputSystem()
{

}

void TankInputSystem::ApplyRightTorque(RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.TorqueMagnitude = 50;
}

void TankInputSystem::ApplyLeftTorque(RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.TorqueMagnitude = -50;
}

void TankInputSystem::ApplyForwardForce(RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.Force.x=3;
    rigidBody2dComponent.Force.y=0;
    rigidBody2dComponent.Force.RotateDegrees(rigidBody2dComponent.RotationAngleDegrees);
}

void TankInputSystem::ApplyBackwardsForce(RigidBody2DComponent &rigidBody2dComponent)
{
    //well... that needs some thought.
    rigidBody2dComponent.Force.x=3;
    rigidBody2dComponent.Force.y=0;
    rigidBody2dComponent.Force.RotateDegrees(rigidBody2dComponent.RotationAngleDegrees);
    rigidBody2dComponent.Force.RotateDegrees(180);
}

void TankInputSystem::KillTorque(RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.TorqueMagnitude = 0;
    rigidBody2dComponent.AngularVelocityMagnitude=0;
}

void TankInputSystem::KillForce(RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.Force.x=0;
    rigidBody2dComponent.Force.y=0;
    rigidBody2dComponent.Velocity.x=0;
    rigidBody2dComponent.Velocity.y=0;
    rigidBody2dComponent.Acceleration.x=0;
    rigidBody2dComponent.Acceleration.y=0;
    rigidBody2dComponent.isAccelerationfrozen=false;

}

void TankInputSystem::fireBullet(Entity &entity)
{
    //tank entity configuration

    //first of all setup initial position and
    //sprite that includes the tank image
    auto bullet_entity = std::make_unique<BulletEntity>();
    bullet_entity->transform_component->RotationAngleDegrees = entity.transform_component->RotationAngleDegrees;

    // TODO: isolate the bullet_entity->rigid_body2d_component from the entity.rigid2dbodycomponent!!!!
    // there is no real reason for directly copying the tank's pointer!
    // Possible errors when the tank object expands with more features!!!
    // The bullet could inherit unpredictable features!
    *bullet_entity->rigid_body2d_component = *entity.rigid_body2d_component;

    //move the bullet design point from the tank design point to the center of the tank
    bullet_entity->rigid_body2d_component->Position.x += entity.sprite_component->sourceRectangle.w / 2.0;
    bullet_entity->rigid_body2d_component->Position.y += entity.sprite_component->sourceRectangle.h / 2.0;

    //calculate a vector for the tank sprite and then add it to the bullet position vector.
    Vector2D PositionTranspose{0,0};
    PositionTranspose.x = entity.sprite_component->sourceRectangle.w / 2.0;
    PositionTranspose.RotateDegrees(entity.transform_component->RotationAngleDegrees);
    bullet_entity->rigid_body2d_component->Position.x += PositionTranspose.x;
    bullet_entity->rigid_body2d_component->Position.y += PositionTranspose.y; //transposed to the front half of tank sprite

    //Will calculate a vector that represent the subtraction of the tank sprite direction vector
    //and the bullet vector. It has to do with the circular draw of the sprites.
    Vector2D CentersDistance{0,0};
    CentersDistance.x = bullet_entity->sprite_component->sourceRectangle.w / 2.0;
    CentersDistance.y = bullet_entity->sprite_component->sourceRectangle.h / 2.0;
    bullet_entity->rigid_body2d_component->Position-=CentersDistance; //subtracted the vectors.
    //At this point the end of the tank vector is on the middle of the bullet circle.
    //A bullet radial vector has to be added for proper representation.

    //The required vector length is the bullet radius. That is the half of the bullet's width.
    Vector2D RadialTranspose{0,0};
    RadialTranspose.x = bullet_entity->sprite_component->sourceRectangle.w / 2.0;

    //We need to rotate the vector so it colinear to the tank's radial vector.
    RadialTranspose.RotateDegrees(bullet_entity->rigid_body2d_component->RotationAngleDegrees);
    bullet_entity->rigid_body2d_component->Position += RadialTranspose;
    //At this point the end of the tank sprite should be aligned with the back mid point of the bullet sprite.

    //Bullet Speed part
    bullet_entity->rigid_body2d_component->Acceleration={0,0};
    bullet_entity->rigid_body2d_component->TorqueMagnitude = 0;

    bullet_entity->rigid_body2d_component->Velocity={1,0}; //set to 1 for bullet to move. 0 for stopped bullet
    bullet_entity->rigid_body2d_component->VelocityMaximumMagnitude = 1;
    bullet_entity->rigid_body2d_component->Velocity.RotateDegrees(entity.rigid_body2d_component->RotationAngleDegrees);

    //collider setup
    auto pointCollider2D = std::make_unique<PointCollider2D>(bullet_entity->rigid_body2d_component->Position, CollisionRespose::RemoveEntity);
    bullet_entity->collider2d_collection_component->colliders.emplace_back(std::move(pointCollider2D));

    game::entityObjects_for_addition.emplace_back(std::move(bullet_entity));
}

void TankInputSystem::handleEvent(SDL_Event &e, Entity &entity)
{
    switch (entity.tank_input_component->state) {
    case State::stopped:
        switch( e.key.keysym.sym )
        {
        case SDLK_w:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move forward
                ApplyForwardForce(*entity.rigid_body2d_component);
                entity.tank_input_component->state = State::forward;

            }
            break;

        case SDLK_s:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move backwards
                entity.rigid_body2d_component->isAccelerationfrozen = false;
                ApplyBackwardsForce(*entity.rigid_body2d_component);
                entity.tank_input_component->state = State::backwards;
            }
            break;

        case SDLK_d:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //rotate cw
                ApplyRightTorque(*entity.rigid_body2d_component);
                entity.tank_input_component->state = State::stoppedRotationClockwise;
            }
            break;

        case SDLK_a:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //rotate ccw
                ApplyLeftTorque(*entity.rigid_body2d_component);
                entity.tank_input_component->state = State::stoppedRotationCounterClockwise;
            }
            break;

        case SDLK_SPACE:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //fire bullet
                TankInputSystem::fireBullet(entity);
            }
            break;
        }

        break;//State::stopped:

    case State::forward:
        switch( e.key.keysym.sym ){
        case SDLK_w:
             if( e.type == SDL_KEYUP){
                 KillForce(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::stopped;
             }
            break;
        case SDLK_s:

             if( e.type == SDL_KEYDOWN){
                 KillForce(*entity.rigid_body2d_component);
                 ApplyBackwardsForce(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::backwards;
             }

            break;
        case SDLK_d:
             if( e.type == SDL_KEYDOWN){

                 ApplyRightTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::forwardRotationClockwise;
             }
            break;
        case SDLK_a:
             if( e.type == SDL_KEYDOWN){
                 ApplyLeftTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::forwardRotationCounterClockwise;
             }
            break;             
        case SDLK_SPACE:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //fire bullet
                TankInputSystem::fireBullet(entity);
            }
            break;
        }
        break;

    case State::backwards:
        switch( e.key.keysym.sym ){
        case SDLK_s:
             if( e.type == SDL_KEYUP){
                 KillForce(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::stopped;
             }
            break;
        case SDLK_w:

             if( e.type == SDL_KEYDOWN){
                 KillForce(*entity.rigid_body2d_component);
                 ApplyForwardForce(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::forward;
             }
            break;
        case SDLK_d:
             if( e.type == SDL_KEYDOWN){
                 ApplyRightTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::backwardsRotationClockwise;
             }
            break;
        case SDLK_a:
             if( e.type == SDL_KEYDOWN){
                 ApplyLeftTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::backwardsRotationCounterClockwise;
             }
            break;
        case SDLK_SPACE:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //fire bullet
                TankInputSystem::fireBullet(entity);
            }
            break;
        }
        break;

    case State::stoppedRotationClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_d:
             if( e.type == SDL_KEYUP){
                 KillTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::stopped;
             }
             break;
        case SDLK_a:
             if( e.type == SDL_KEYDOWN){
                 ApplyLeftTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::stoppedRotationCounterClockwise;
             }
             break;
        case SDLK_w:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move forward
                ApplyForwardForce(*entity.rigid_body2d_component);
                entity.tank_input_component->state = State::forwardRotationClockwise;
            }
            break;

        case SDLK_s:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move backwards
                ApplyBackwardsForce(*entity.rigid_body2d_component);
                entity.tank_input_component->state = State::backwardsRotationClockwise;
            }
            break;
        case SDLK_SPACE:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //fire bullet
                TankInputSystem::fireBullet(entity);
            }
            break;
        }
        break;

    case State::stoppedRotationCounterClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_a:
             if( e.type == SDL_KEYUP){
                 KillTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::stopped;
             }
            break;

        case SDLK_d:
             if( e.type == SDL_KEYDOWN){
                 ApplyRightTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::stoppedRotationClockwise;
             }
            break;

        case SDLK_w:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move forward
                ApplyForwardForce(*entity.rigid_body2d_component);
                entity.tank_input_component->state = State::forwardRotationCounterClockwise;
            }
            break;

        case SDLK_s:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move backwards
                ApplyBackwardsForce(*entity.rigid_body2d_component);
                entity.tank_input_component->state = State::backwardsRotationCounterClockwise;
            }
            break;
        case SDLK_SPACE:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //fire bullet
                TankInputSystem::fireBullet(entity);
            }
            break;
        }
        break;

    case State::forwardRotationClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_d:
             if( e.type == SDL_KEYUP){                 
                 KillTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::forward;
             }
            break;
        case SDLK_w:
             if( e.type == SDL_KEYUP){
                 KillForce(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::stoppedRotationClockwise;
             }

            break;
        case SDLK_a:
             if( e.type == SDL_KEYDOWN){
                 ApplyLeftTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::forwardRotationCounterClockwise;
             }
            break;

        case SDLK_s:
             if( e.type == SDL_KEYDOWN){
                 ApplyBackwardsForce(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::backwardsRotationClockwise;
             }
            break;
        case SDLK_SPACE:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //fire bullet
                TankInputSystem::fireBullet(entity);
            }
            break;
        }
        break;

    case State::forwardRotationCounterClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_a:
             if( e.type == SDL_KEYUP){
                 KillTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::forward;
             }
            break;
        case SDLK_w:
             if( e.type == SDL_KEYUP){
                 KillForce(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::stoppedRotationCounterClockwise;
             }

            break;

        case SDLK_d:
             if( e.type == SDL_KEYDOWN){
                 ApplyRightTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::forwardRotationClockwise;
             }
            break;

        case SDLK_s:
             if( e.type == SDL_KEYDOWN){
                 ApplyBackwardsForce(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::backwardsRotationCounterClockwise;
             }
            break;

        case SDLK_SPACE:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //fire bullet
                TankInputSystem::fireBullet(entity);
            }
            break;
        }
        break;

    case State::backwardsRotationClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_d:
             if( e.type == SDL_KEYUP){
                 KillTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::backwards;
             }
            break;
        case SDLK_s:
             if( e.type == SDL_KEYUP){
                 KillForce(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::stoppedRotationClockwise;
             }

            break;

        case SDLK_a:
             if( e.type == SDL_KEYDOWN){
                 ApplyLeftTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::backwardsRotationCounterClockwise;
             }
            break;

        case SDLK_w:
             if( e.type == SDL_KEYDOWN){
                 ApplyForwardForce(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::forwardRotationClockwise;
             }
            break;

        case SDLK_SPACE:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //fire bullet
                TankInputSystem::fireBullet(entity);
            }
            break;

        }
        break;

    case State::backwardsRotationCounterClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_a:
             if( e.type == SDL_KEYUP){
                 KillTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::backwards;
             }
            break;
        case SDLK_s:
             if( e.type == SDL_KEYUP){
                 KillForce(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::stoppedRotationCounterClockwise;
             }

            break;

        case SDLK_d:
             if( e.type == SDL_KEYDOWN){
                 ApplyRightTorque(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::backwardsRotationClockwise;
             }
            break;

        case SDLK_w:
             if( e.type == SDL_KEYDOWN){
                 ApplyForwardForce(*entity.rigid_body2d_component);
                 entity.tank_input_component->state = State::forwardRotationCounterClockwise;
             }
            break;

        case SDLK_SPACE:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //fire bullet
                TankInputSystem::fireBullet(entity);
            }
            break;
        }
        break;

    }//switch
}//TankInputSystem::handleEvent
