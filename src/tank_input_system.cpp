#include "tank_input_system.h"

TankInputSystem::TankInputSystem()
{

}

void TankInputSystem::handleEvent(SDL_Event &e, TankInputComponent &tankInputComponent , RigidBody2DComponent &rigidBody2dComponent)
{
    switch (tankInputComponent.state) {
    case State::stopped:
        switch( e.key.keysym.sym )
        {
        case SDLK_w:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                tankInputComponent.state = State::moveForward;
                rigidBody2dComponent.isAccelerationfrozen = false;
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
                tankInputComponent.state = State::moveForward;
                rigidBody2dComponent.isAccelerationfrozen = false;
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
                tankInputComponent.state = State::moveForward;
                rigidBody2dComponent.isAccelerationfrozen = false;
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
