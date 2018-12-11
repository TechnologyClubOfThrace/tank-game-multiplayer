#include "render_system.h"

RenderSystem::RenderSystem()
{

}

void RenderSystem::Render(TransformComponent &transformComponent, SpriteComponent &spriteComponent, std::vector<ViewPort> &viewports)
{
    const SDL_Rect destinationRectangle = { static_cast<int>(round(transformComponent.Position.x - static_cast<double>(viewports[0].camera.frame.x))),
                                            static_cast<int>(round(transformComponent.Position.y - static_cast<double>(viewports[0].camera.frame.y))),
                                            spriteComponent.rect.w,
                                            spriteComponent.rect.h};

    int res = SDL_RenderCopyEx(renderer,
                     spriteComponent.texture,
                     &spriteComponent.rect,//source rectangle
                     &destinationRectangle,//destination rectangle
                     0,//angle
                     nullptr,//center
                     SDL_RendererFlip::SDL_FLIP_NONE
                );

   // std::cout << "res: " << res << " ,sprite w: " << spriteComponent.rect.w << std::endl;
}

//loads a texture from an image file
bool RenderSystem::CreateTextureFromFile(std::string path, SDL_Renderer* renderer, SpriteComponent &spriteComponent)
{
    if (spriteComponent.texture != nullptr){
        SDL_DestroyTexture(spriteComponent.texture);
        spriteComponent.texture = nullptr;
        spriteComponent.rect.x = 0;
        spriteComponent.rect.y = 0;
        spriteComponent.rect.h = 0;
        spriteComponent.rect.w = 0;
    }

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        //SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        spriteComponent.texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(spriteComponent.texture == nullptr)
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            spriteComponent.rect.x = 0;
            spriteComponent.rect.y = 0;
            spriteComponent.rect.w = loadedSurface->w;
            spriteComponent.rect.h = loadedSurface->h;
            // std::cout << "create texture > sprite w: " << spriteComponent.rect.w << std::endl;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    return spriteComponent.texture != nullptr;
}
