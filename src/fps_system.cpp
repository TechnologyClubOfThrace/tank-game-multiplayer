#include "fps_system.h"

FpsSystem::FpsSystem()
{
}

FpsSystem::~FpsSystem()
{
}

//SDL_GetCPUCacheLineSize
//SDL_GetCurrentVideoDriver
//SDL_GetCPUCount
//SDL_GetPlatform()
//SDL_GetVersion(v)
void FpsSystem::Update(const std::chrono::milliseconds::rep &deltaTime, const FpsEntity &fpsEntity)
{
    fpsEntity.fps_component->fps = std::string("Fps: ").append(std::to_string(static_cast<int>(deltaTime > 0 ? round(1000/deltaTime) : 0))).append(
                "\nTotal entities: " + std::to_string(fpsEntity.fps_component->entities_count));
    LoadFromRenderedText(fpsEntity);

    //fps_str = fps > 0 ? (fps < 5000 ? "FPS: " + std::to_string(fps) : fps_str) : fps_str;

    /*
    fps_str = (fps > 0 ? "fps: " + std::to_string(fps) : fps_str).append(
                "\nCPU Cores: ").append(std::to_string(SDL_GetCPUCount())).append(
                "\nCPU L1 Cache line size: ").append(std::to_string(SDL_GetCPUCacheLineSize()).append(" bytes"));
                */

}

//loads a texture from string
bool FpsSystem::LoadFromRenderedText(const FpsEntity &fpsEntity)
{
    //Render text surface
    if (fpsEntity.sprite_component->texture){
        SDL_DestroyTexture(fpsEntity.sprite_component->texture);
    }

    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(fpsEntity.fps_component->font, fpsEntity.fps_component->fps.c_str(), fpsEntity.fps_component->textColor, 1000 );
    if( textSurface != nullptr )
    {
        //Create texture from surface pixels
        fpsEntity.sprite_component->texture = SDL_CreateTextureFromSurface(RenderUtils::windowRenderer, textSurface );
        if(fpsEntity.sprite_component->texture == nullptr )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimension
            fpsEntity.sprite_component->sourceRectangle.w = textSurface->w;
            fpsEntity.sprite_component->sourceRectangle.h = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    return fpsEntity.sprite_component->texture != nullptr;
}
