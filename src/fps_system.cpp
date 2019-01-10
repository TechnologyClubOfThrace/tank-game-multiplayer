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
void FpsSystem::Update(const std::chrono::milliseconds::rep &deltaTime,
                       std::unique_ptr<SpriteComponent> &spriteComponent,
                       std::unique_ptr<FpsComponent> &fpsComponent)
{
    fpsComponent->fps = std::to_string(static_cast<int>(deltaTime > 0 ? round(1000/deltaTime) : 0));
    loadFromRenderedText(spriteComponent, fpsComponent);

    //fps_str = fps > 0 ? (fps < 5000 ? "FPS: " + std::to_string(fps) : fps_str) : fps_str;

    /*
    fps_str = (fps > 0 ? "fps: " + std::to_string(fps) : fps_str).append(
                "\nCPU Cores: ").append(std::to_string(SDL_GetCPUCount())).append(
                "\nCPU L1 Cache line size: ").append(std::to_string(SDL_GetCPUCacheLineSize()).append(" bytes"));
                */

}

//loads a texture from string
bool FpsSystem::loadFromRenderedText( std::unique_ptr<SpriteComponent> &spriteComponent,  std::unique_ptr<FpsComponent> &fpsComponent)
{
    //Render text surface
    if (spriteComponent->texture){
        SDL_DestroyTexture(spriteComponent->texture);
    }

    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(fpsComponent->font, fpsComponent->fps.c_str(), fpsComponent->textColor, 1000 );
    if( textSurface != nullptr )
    {
        //Create texture from surface pixels
        spriteComponent->texture = SDL_CreateTextureFromSurface(RenderUtils::windowRenderer, textSurface );
        if( spriteComponent->texture == nullptr )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimension
            spriteComponent->sourceRectangle.w = textSurface->w;
            spriteComponent->sourceRectangle.h = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    return spriteComponent->texture != nullptr;
}
