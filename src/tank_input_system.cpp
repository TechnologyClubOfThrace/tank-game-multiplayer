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

void TankInputSystem::handleEvent(SDL_Event &e, TankInputComponent &tankInputComponent , RigidBody2DComponent &rigidBody2dComponent)
{
    switch (tankInputComponent.state) {
    case State::stopped:
        HandleUserInput(e, tankInputComponent, rigidBody2dComponent);
        break;
    case State::moveForward:
         HandleUserInput(e, tankInputComponent, rigidBody2dComponent);
         break;
    case State::moveBackwards:
         HandleUserInput(e, tankInputComponent, rigidBody2dComponent);
         break;
    case State::stoppedRotationClockwise:
         HandleUserInput(e, tankInputComponent, rigidBody2dComponent);
         break;
    }
}

void TankInputSystem::HandleUserInput(SDL_Event &e, TankInputComponent &tankInputComponent , RigidBody2DComponent &rigidBody2dComponent)
{
    switch( e.key.keysym.sym )
    {
    case SDLK_w:
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
            tankInputComponent.state = State::moveForward;
            rigidBody2dComponent.isAccelerationfrozen = false;
            rigidBody2dComponent.Velocity.x = 0;
            rigidBody2dComponent.Velocity.y = 0;
        } else if (e.type == SDL_KEYUP && e.key.repeat == 0 ){
            tankInputComponent.state = State::stopped;
            rigidBody2dComponent.isAccelerationfrozen = true;
            rigidBody2dComponent.Velocity.x = 0;
            rigidBody2dComponent.Velocity.y = 0;
        }
        break;
    case SDLK_s:
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
            tankInputComponent.state = State::moveBackwards;
            rigidBody2dComponent.isAccelerationfrozen = false;
            rigidBody2dComponent.Velocity.x = 0;
            rigidBody2dComponent.Velocity.y = 0;
        } else if (e.type == SDL_KEYUP && e.key.repeat == 0 ){
            tankInputComponent.state = State::stopped;
            rigidBody2dComponent.isAccelerationfrozen = true;
            rigidBody2dComponent.Velocity.x = 0;
            rigidBody2dComponent.Velocity.y = 0;
        }
        break;
    case SDLK_d: //clockwise rotation
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
            tankInputComponent.state = State::stoppedRotationClockwise;
        } else if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
            tankInputComponent.state = State::stoppedRotationClockwise;
        }
        break;
    case SDLK_a:
        break;
    }
}
