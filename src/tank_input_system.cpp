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

void TankInputSystem::handleEvent(SDL_Event &e, TankInputComponent &tankInputComponent , RigidBody2DComponent &rigidBody2dComponent)
{
    switch (tankInputComponent.state) {
    case State::stopped:
        if (e.button.state == SDL_PRESSED) {
            //move forward
            rigidBody2dComponent.isAccelerationfrozen = false;
            rigidBody2dComponent.Force = rigidBody2dComponent.DirectionalForce;
            rigidBody2dComponent.Force.RotateDegrees(transformComponent.RotationAngleDegrees);
            rigidBody2dComponent.Acceleration = rigidBody2dComponent.Force / rigidBody2dComponent.Mass;
            tankInputComponent.state = State::forward;
        }
        switch( e.key.keysym.sym )
        {
        case SDLK_w:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move forward
                ApplyForwardForce(rigidBody2dComponent);
                tankInputComponent.state = State::forward;

            }
            break;

        case SDLK_s:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move backwards
                rigidBody2dComponent.isAccelerationfrozen = false;
                ApplyBackwardsForce(rigidBody2dComponent);
                tankInputComponent.state = State::backwards;
            }
            break;

        case SDLK_d:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //rotate cw
                ApplyRightTorque(rigidBody2dComponent);
                tankInputComponent.state = State::stoppedRotationClockwise;
            }
            break;

        case SDLK_a:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //rotate ccw
                ApplyLeftTorque(rigidBody2dComponent);
                tankInputComponent.state = State::stoppedRotationCounterClockwise;
            }
            break;
        }

        break;//State::stopped:

    case State::forward:
        switch( e.key.keysym.sym ){
        case SDLK_w:
             if( e.type == SDL_KEYUP){
                 KillForce(rigidBody2dComponent);
                 tankInputComponent.state = State::stopped;
             }
            break;
        case SDLK_s:

             if( e.type == SDL_KEYDOWN){
                 KillForce(rigidBody2dComponent);
                 ApplyBackwardsForce(rigidBody2dComponent);
                 tankInputComponent.state = State::backwards;
             }

            break;
        case SDLK_d:
             if( e.type == SDL_KEYDOWN){

                 ApplyRightTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::forwardRotationClockwise;
             }
            break;
        case SDLK_a:
             if( e.type == SDL_KEYDOWN){
                 ApplyLeftTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::forwardRotationCounterClockwise;
             }
            break;
        }
        break;

    case State::backwards:
        switch( e.key.keysym.sym ){
        case SDLK_s:
             if( e.type == SDL_KEYUP){
                 KillForce(rigidBody2dComponent);
                 tankInputComponent.state = State::stopped;
             }
            break;
        case SDLK_w:

             if( e.type == SDL_KEYDOWN){
                 KillForce(rigidBody2dComponent);
                 ApplyForwardForce(rigidBody2dComponent);
                 tankInputComponent.state = State::forward;
             }
            break;
        case SDLK_d:
             if( e.type == SDL_KEYDOWN){
                 ApplyRightTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::backwardsRotationClockwise;
             }
            break;
        case SDLK_a:
             if( e.type == SDL_KEYDOWN){
                 ApplyLeftTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::backwardsRotationCounterClockwise;
             }
            break;
        }
        break;

    case State::stoppedRotationClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_d:
             if( e.type == SDL_KEYUP){
                 KillTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::stopped;
             }
             break;
        case SDLK_a:
             if( e.type == SDL_KEYDOWN){
                 ApplyLeftTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::stoppedRotationCounterClockwise;
             }
             break;
        case SDLK_w:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move forward
                ApplyForwardForce(rigidBody2dComponent);
                tankInputComponent.state = State::forwardRotationClockwise;
            }
            break;

        case SDLK_s:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move backwards
                ApplyBackwardsForce(rigidBody2dComponent);
                tankInputComponent.state = State::backwardsRotationClockwise;
            }
            break;

        }
        break;

    case State::stoppedRotationCounterClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_a:
             if( e.type == SDL_KEYUP){
                 KillTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::stopped;
             }
            break;

        case SDLK_d:
             if( e.type == SDL_KEYDOWN){
                 ApplyRightTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::stoppedRotationClockwise;
             }
            break;

        case SDLK_w:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move forward
                ApplyForwardForce(rigidBody2dComponent);
                tankInputComponent.state = State::forwardRotationCounterClockwise;
            }
            break;

        case SDLK_s:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move backwards
                ApplyBackwardsForce(rigidBody2dComponent);
                tankInputComponent.state = State::backwardsRotationCounterClockwise;
            }
            break;

        }
        break;

    case State::forwardRotationClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_d:
             if( e.type == SDL_KEYUP){                 
                 KillTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::forward;
             }
            break;
        case SDLK_w:
             if( e.type == SDL_KEYUP){
                 KillForce(rigidBody2dComponent);
                 tankInputComponent.state = State::stoppedRotationClockwise;
             }

            break;
        case SDLK_a:
             if( e.type == SDL_KEYDOWN){
                 ApplyLeftTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::forwardRotationCounterClockwise;
             }
            break;

        case SDLK_s:
             if( e.type == SDL_KEYDOWN){
                 ApplyBackwardsForce(rigidBody2dComponent);
                 tankInputComponent.state = State::backwardsRotationClockwise;
             }
            break;
        }
        break;

    case State::forwardRotationCounterClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_a:
             if( e.type == SDL_KEYUP){
                 KillTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::forward;
             }
            break;
        case SDLK_w:
             if( e.type == SDL_KEYUP){
                 KillForce(rigidBody2dComponent);
                 tankInputComponent.state = State::stoppedRotationCounterClockwise;
             }

            break;

        case SDLK_d:
             if( e.type == SDL_KEYDOWN){
                 ApplyRightTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::forwardRotationClockwise;
             }
            break;

        case SDLK_s:
             if( e.type == SDL_KEYDOWN){
                 ApplyBackwardsForce(rigidBody2dComponent);
                 tankInputComponent.state = State::backwardsRotationCounterClockwise;
             }
            break;

        }
        break;

    case State::backwardsRotationClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_d:
             if( e.type == SDL_KEYUP){
                 KillTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::backwards;
             }
            break;
        case SDLK_s:
             if( e.type == SDL_KEYUP){
                 KillForce(rigidBody2dComponent);
                 tankInputComponent.state = State::stoppedRotationClockwise;
             }

            break;

        case SDLK_a:
             if( e.type == SDL_KEYDOWN){
                 ApplyLeftTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::backwardsRotationCounterClockwise;
             }
            break;

        case SDLK_w:
             if( e.type == SDL_KEYDOWN){
                 ApplyForwardForce(rigidBody2dComponent);
                 tankInputComponent.state = State::forwardRotationClockwise;
             }
            break;

        }
        break;

    case State::backwardsRotationCounterClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_a:
             if( e.type == SDL_KEYUP){
                 KillTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::backwards;
             }
            break;
        case SDLK_s:
             if( e.type == SDL_KEYUP){
                 KillForce(rigidBody2dComponent);
                 tankInputComponent.state = State::stoppedRotationCounterClockwise;
             }

            break;

        case SDLK_d:
             if( e.type == SDL_KEYDOWN){
                 ApplyRightTorque(rigidBody2dComponent);
                 tankInputComponent.state = State::backwardsRotationClockwise;
             }
            break;

        case SDLK_w:
             if( e.type == SDL_KEYDOWN){
                 ApplyForwardForce(rigidBody2dComponent);
                 tankInputComponent.state = State::forwardRotationCounterClockwise;
             }
            break;
        }
        break;

    }//switch
}//TankInputSystem::handleEvent
