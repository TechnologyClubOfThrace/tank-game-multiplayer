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

void TankInputSystem::handleEvent(SDL_Event &e, TankInputComponent &tankInputComponent , RigidBody2DComponent &rigidBody2dComponent, TransformComponent &transformComponent)
{
    switch (tankInputComponent.state) {
    case State::stopped:
        switch( e.key.keysym.sym )
        {
        case SDLK_w:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move forward
                rigidBody2dComponent.isAccelerationfrozen = false;
                rigidBody2dComponent.Force = rigidBody2dComponent.DirectionalForce;
                rigidBody2dComponent.Force.RotateDegrees(transformComponent.RotationAngleDegrees);
                rigidBody2dComponent.Acceleration = rigidBody2dComponent.Force / rigidBody2dComponent.Mass;
                tankInputComponent.state = State::forward;
            }
            break;

        case SDLK_s:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //move backwards
                rigidBody2dComponent.isAccelerationfrozen = false;
                rigidBody2dComponent.Force = rigidBody2dComponent.DirectionalForce;
                rigidBody2dComponent.Force.RotateDegrees(transformComponent.RotationAngleDegrees);
                rigidBody2dComponent.Acceleration = rigidBody2dComponent.Force / rigidBody2dComponent.Mass;
                tankInputComponent.state = State::backwards;
            }
            break;

        case SDLK_d:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //rotate cw
                rigidBody2dComponent.isAngularAccelerationfrozen = false;
                tankInputComponent.state = State::stoppedRotationClockwise;
            }
            break;

        case SDLK_a:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //rotate ccw
                rigidBody2dComponent.isAngularAccelerationfrozen = false;
                tankInputComponent.state = State::stoppedRotationCounterClockwise;
            }
            break;
        }

        break;//State::stopped:

    case State::forward:
        switch( e.key.keysym.sym ){
        case SDLK_w:
             if( e.type == SDL_KEYUP){
                 tankInputComponent.state = State::stopped;
                 rigidBody2dComponent.Velocity.setZeroMagnitude();
             }
            break;
        case SDLK_s:

             if( e.type == SDL_KEYDOWN){
                 tankInputComponent.state = State::backwards;
                 rigidBody2dComponent.isAccelerationfrozen = false;
                 rigidBody2dComponent.Velocity.setZeroMagnitude();
             }

            break;
        case SDLK_d:
             if( e.type == SDL_KEYDOWN){
                 tankInputComponent.state = State::forwardRotationClockwise;
                 rigidBody2dComponent.isAngularAccelerationfrozen = false;
             }
            break;
        case SDLK_a:
             if( e.type == SDL_KEYDOWN){
                 tankInputComponent.state = State::forwardRotationCounterClockwise;
                 rigidBody2dComponent.isAngularAccelerationfrozen = false;
             }
            break;
        }
        break;

    case State::backwards:
        switch( e.key.keysym.sym ){
        case SDLK_s:
             if( e.type == SDL_KEYUP){
                 tankInputComponent.state = State::stopped;
                 rigidBody2dComponent.Velocity.setZeroMagnitude();
             }
            break;
        case SDLK_w:

             if( e.type == SDL_KEYDOWN){
                 rigidBody2dComponent.isAccelerationfrozen = false;
                 rigidBody2dComponent.Velocity.setZeroMagnitude();
                 tankInputComponent.state = State::forward;
             }
            break;
        case SDLK_d:
             if( e.type == SDL_KEYDOWN){
                 tankInputComponent.state = State::backwardsRotationClockwise;
                 rigidBody2dComponent.isAngularAccelerationfrozen = false;
             }
            break;
        case SDLK_a:
             if( e.type == SDL_KEYDOWN){
                 tankInputComponent.state = State::backwardsRotationCounterClockwise;
                 rigidBody2dComponent.isAngularAccelerationfrozen = false;
             }
            break;
        }
        break;

    case State::stoppedRotationClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_d:
             if( e.type == SDL_KEYUP){
                 rigidBody2dComponent.AngularVelocityMagnitude = 0;
                 tankInputComponent.state = State::stopped;
             }
             break;
        case SDLK_a:
             if( e.type == SDL_KEYDOWN){
                 rigidBody2dComponent.AngularVelocityMagnitude = 0;
                 rigidBody2dComponent.isAngularAccelerationfrozen = false;
                 tankInputComponent.state = State::stoppedRotationCounterClockwise;
             }
             break;
        }
        break;

    case State::stoppedRotationCounterClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_a:
             if( e.type == SDL_KEYUP){
                 rigidBody2dComponent.AngularVelocityMagnitude = 0;
                 tankInputComponent.state = State::stopped;
             }
            break;
        case SDLK_d:
             if( e.type == SDL_KEYDOWN){
                 rigidBody2dComponent.AngularVelocityMagnitude = 0;
                 rigidBody2dComponent.isAngularAccelerationfrozen = false;
                 tankInputComponent.state = State::stoppedRotationClockwise;
             }
            break;
        }
        break;

    case State::forwardRotationClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_d:
             if( e.type == SDL_KEYUP){
                 tankInputComponent.state = State::forward;
                 rigidBody2dComponent.AngularVelocityMagnitude = 0;
             }
            break;
        case SDLK_w:
             if( e.type == SDL_KEYUP){
                 tankInputComponent.state = State::stoppedRotationClockwise;
                 rigidBody2dComponent.Velocity.setZeroMagnitude();
             }

            break;
        }
        break;

    case State::forwardRotationCounterClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_a:
             if( e.type == SDL_KEYUP){
                 tankInputComponent.state = State::forward;
                 rigidBody2dComponent.AngularVelocityMagnitude = 0;
             }
            break;
        case SDLK_w:
             if( e.type == SDL_KEYUP){
                 tankInputComponent.state = State::stoppedRotationCounterClockwise;
                 rigidBody2dComponent.Velocity.setZeroMagnitude();
             }

            break;
        }
        break;

    case State::backwardsRotationClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_d:
             if( e.type == SDL_KEYUP){
                 tankInputComponent.state = State::backwards;
                 rigidBody2dComponent.AngularVelocityMagnitude = 0;
             }
            break;
        case SDLK_s:
             if( e.type == SDL_KEYUP){
                 tankInputComponent.state = State::stoppedRotationClockwise;
                 rigidBody2dComponent.Velocity.setZeroMagnitude();
             }

            break;
        }
        break;

    case State::backwardsRotationCounterClockwise:
        switch( e.key.keysym.sym ){
        case SDLK_a:
             if( e.type == SDL_KEYUP){
                 tankInputComponent.state = State::backwards;
                 rigidBody2dComponent.AngularVelocityMagnitude = 0;
             }
            break;
        case SDLK_s:
             if( e.type == SDL_KEYUP){
                 tankInputComponent.state = State::stoppedRotationCounterClockwise;
                 rigidBody2dComponent.Velocity.setZeroMagnitude();
             }

            break;
        }
        break;

    }//switch
}//TankInputSystem::handleEvent
