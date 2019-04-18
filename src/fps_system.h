#ifndef FPS_SYSTEM_H
#define FPS_SYSTEM_H

#include <SDL_ttf.h>
#include <chrono>
#include "fps_entity.h"
#include "scene_manager.h"
#include "render_utils.h"

class FpsSystem
{
public:
    FpsSystem();
    ~FpsSystem();
    static void Update(const double &deltaTime, const FpsEntity &fpsEntity);
private:
    static bool LoadFromRenderedText(const FpsEntity &fpsEntity);
};

#endif // FPS_SYSTEM_H
