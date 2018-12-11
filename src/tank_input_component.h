#ifndef TANK_INPUT_COMPONENT_H
#define TANK_INPUT_COMPONENT_H

enum class State
{
    stopped,
    moveForward,
    moveBackwards
};

class TankInputComponent
{
public:
    TankInputComponent();

    State state {State::stopped};

};

#endif // TANK_INPUT_COMPONENT_H
