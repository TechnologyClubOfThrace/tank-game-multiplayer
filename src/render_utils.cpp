#include "render_utils.h"

//static variables
SDL_Renderer* RenderUtils::windowRenderer;

RenderUtils::RenderUtils()
{

}
//loads a texture from an image file
bool RenderUtils::LoadTextureFromFile(std::string path, SDL_Texture*& texture)
{
    //Get rid of preexisting texture
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
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
        texture = SDL_CreateTextureFromSurface(RenderUtils::windowRenderer, loadedSurface );
        if( texture == nullptr )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            //mWidth = loadedSurface->w;
            //mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    return texture != nullptr;
}

//loads a texture from an image file

bool RenderUtils::LoadTextureFromFile(std::string path, SpriteComponent &spriteComponent)
{
    LoadTextureFromFile(path, spriteComponent.texture);

    if (spriteComponent.texture == nullptr){
        spriteComponent.sourceRectangle.x = 0;
        spriteComponent.sourceRectangle.y = 0;
        spriteComponent.sourceRectangle.h = 0;
        spriteComponent.sourceRectangle.w = 0;
    } else {
        SDL_QueryTexture(spriteComponent.texture, nullptr, nullptr, &spriteComponent.sourceRectangle.w, &spriteComponent.sourceRectangle.h);
        spriteComponent.sourceRectangle.x = 0;
        spriteComponent.sourceRectangle.y = 0;
        spriteComponent.destinationRectangle = spriteComponent.sourceRectangle;
    }

    return spriteComponent.texture != nullptr;
}

void RenderUtils::setColor(SDL_Texture *&texture, Uint8 red, Uint8 green, Uint8 blue)
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( texture, red, green, blue );
}

void RenderUtils::setBlendMode(SDL_Texture *&texture, SDL_BlendMode blending)
{
    //Set blending function
    SDL_SetTextureBlendMode(texture, blending);
}

void RenderUtils::setAlpha(SDL_Texture *&texture, Uint8 alpha)
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod(texture, alpha);
}

