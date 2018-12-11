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
