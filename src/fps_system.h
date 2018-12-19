#ifndef FPS_SYSTEM_H
#define FPS_SYSTEM_H

#include <SDL_ttf.h>
#include <chrono>
#include "fps_component.h"
#include "transform_component.h"
#include "sprite_component.h"
#include "scene_manager.h"
#include "render_utils.h"

class FpsSystem
{
public:
    FpsSystem();
    ~FpsSystem();

    void Update(const std::chrono::milliseconds::rep &deltaTime,
                std::unique_ptr<SpriteComponent> &spriteComponent,
                std::unique_ptr<FpsComponent> &fpsComponent);
    bool loadFromRenderedText( std::unique_ptr<SpriteComponent> &spriteComponent,  std::unique_ptr<FpsComponent> &fpsComponent);
};

#endif // FPS_SYSTEM_H
