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

TankInputSystem::TankInputSystem()
{

}

void TankInputSystem::ApplyRightTorque(RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.TorqueMagnitude = 100;
}

void TankInputSystem::ApplyLeftTorque(RigidBody2DComponent &rigidBody2dComponent)
{
    rigidBody2dComponent.TorqueMagnitude = -100;
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
    bullet_entity->transform_component->Position.x = entity.transform_component->Position.x;
    bullet_entity->transform_component->Position.y = entity.transform_component->Position.y;
    bullet_entity->transform_component->RotationAngleDegrees = entity.transform_component->RotationAngleDegrees;
    RenderUtils::LoadTextureFromFile("bullet_w65h20.png", *bullet_entity->sprite_component);
    //bullet_entity->transform_component->RotationAngleDegrees = 0;
    /*
    //initial values for tank entity physics
    tank_entity->rigid_body2d_component->Acceleration.x = 0.000;
    tank_entity->rigid_body2d_component->Force = {0, 0};
    tank_entity->rigid_body2d_component->TorqueMagnitude = 000;
    tank_entity->rigid_body2d_component->Mass = 10000;
    tank_entity->rigid_body2d_component->AngularVelocityMaximumMagnitude = 0.06;
    tank_entity->rigid_body2d_component->AngularVelocityMagnitude = 0;
    tank_entity->rigid_body2d_component->VelocityMaximumMagnitude = 0.10;
    tank_entity->rigid_body2d_component->MoI = tank_entity->rigid_body2d_component->Mass;
    tank_entity->rigid_body2d_component->AngularAccelerationMagnitude = tank_entity->rigid_body2d_component->TorqueMagnitude/tank_entity->rigid_body2d_component->MoI;
    tank_entity->rigid_body2d_component->isAccelerationfrozen = false;
    tank_entity->rigid_body2d_component->isAngularAccelerationfrozen = false;
    */

    //insert the tank entity into the entities collection
    int sa =1 ;
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
        }
        break;

    }//switch
}//TankInputSystem::handleEvent
