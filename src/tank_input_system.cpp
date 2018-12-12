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

void TankInputSystem::handleEvent(SDL_Event &e, TankInputComponent &tankInputComponent)
{
    switch (tankInputComponent.state) {
    case State::stopped:
        switch( e.key.keysym.sym )
        {
        case SDLK_w:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //setAngleDirection(e.key.keysym);
                tankInputComponent.state = State::moveForward;
                //Velocity.x = NormalTankSpeed;
            }
            break;
        case SDLK_s:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                tankInputComponent.state = State::moveBackwards;
            }
            break;
        case SDLK_a:
            break;
        case SDLK_d:
            break;
        }
        break;
    case State::moveForward:
        switch( e.key.keysym.sym )
        {
        case SDLK_w:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //setAngleDirection(e.key.keysym);
                tankInputComponent.state = State::moveForward;
                //Velocity.x = NormalTankSpeed;
            }
            break;
        case SDLK_s:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                tankInputComponent.state = State::moveBackwards;
            }
            break;
        case SDLK_a:
            break;
        case SDLK_d:
            break;
        }
        break;
    case State::moveBackwards:
        switch( e.key.keysym.sym )
        {
        case SDLK_w:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //setAngleDirection(e.key.keysym);
                tankInputComponent.state = State::moveForward;
                //Velocity.x = NormalTankSpeed;
            }
            break;
        case SDLK_s:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                tankInputComponent.state = State::moveBackwards;
            }
            break;
        case SDLK_a:
            break;
        case SDLK_d:
            break;
        }
        break;
    }
}
