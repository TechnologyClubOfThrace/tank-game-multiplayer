#ifndef ZOOM_INPUT_SYSTEM_H
#define ZOOM_INPUT_SYSTEM_H

#include <SDL.h>
#include <memory>
#include <chrono>
#include "entity.h"

class ZoomInputSystem
{
public:
    ZoomInputSystem();

    static void HandleEvent(const SDL_Event &e, const Entity& entity);
    static void Update(const std::chrono::milliseconds::rep &deltaTime, const Entity &entity);
};

#endif // ZOOM_INPUT_SYSTEM_H
