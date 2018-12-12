#ifndef TANK_INPUT_SYSTEM_H
#define TANK_INPUT_SYSTEM_H

#include <SDL.h>
#include "tank_input_component.h"
#include "rigid_body2d_component.h"

class TankInputSystem
{
public:
    TankInputSystem();

    void handleEvent(SDL_Event &e, TankInputComponent &tankInputComponent, RigidBody2DComponent &rigidBody2dComponent);
};

#endif // TANK_INPUT_SYSTEM_H
