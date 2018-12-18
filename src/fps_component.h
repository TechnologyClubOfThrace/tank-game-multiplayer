#ifndef FPS_COMPONENT_H
#define FPS_COMPONENT_H

#include <SDL_ttf.h>
#include <string>

class FpsComponent
{
public:
    FpsComponent();
    ~FpsComponent();

    std::string fps {};
    bool displayFpsCounter = true;
    TTF_Font * font = nullptr;
    SDL_Color textColor = { 204, 0, 204, 255 };
};

#endif // FPS_COMPONENT_H
