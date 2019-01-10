#include "render_utils.h"

//static variables
SDL_Renderer* RenderUtils::windowRenderer;

RenderUtils::RenderUtils()
{

}

//loads a texture from an image file
bool RenderUtils::LoadSpriteFromFile(std::string path, SpriteComponent& sprite)
{
    //std::cout << "[ENTERED] LoadTextureFromFile" << std::endl;
    //Get rid of preexisting texture
    if(sprite.texture != nullptr){
        SDL_DestroyTexture(sprite.texture);
        sprite.texture = nullptr;
    }

    //Load image at specified path
    //std::cout << "[WILL] SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); PATH: " << path << std::endl;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr )
    {
        std::cout << "Unable to load image: " << path.c_str() << " ! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        //std::cout << "[OK] SDL_Surface* loadedSurface = IMG_Load( path.c_str() );" << std::endl;
        //Create texture from surface pixels
        //std::cout << "[WILL]  texture = SDL_CreateTextureFromSurface(RenderUtils::windowRenderer, loadedSurface );" << std::endl;
        sprite.texture = SDL_CreateTextureFromSurface(RenderUtils::windowRenderer, loadedSurface );
        sprite.sourceRectangle.x = 0;
        sprite.sourceRectangle.y = 0;
        if(sprite.texture == nullptr)
        {
            std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
            sprite.sourceRectangle.w = 0;
            sprite.sourceRectangle.h = 0;
        }
        else
        {
            //Get image dimensions
            sprite.sourceRectangle.w = loadedSurface->w;
            sprite.sourceRectangle.h = loadedSurface->h;
        }
        //std::cout << "[OK]  texture = SDL_CreateTextureFromSurface(RenderUtils::windowRenderer, loadedSurface );" << std::endl;

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    return sprite.texture != nullptr;
}

//loads a texture from an image file. todo: should remove this method.
bool RenderUtils::LoadTextureFromFile(std::string path, SDL_Texture*& texture)
{
    //std::cout << "[ENTERED] LoadTextureFromFile" << std::endl;
    //Get rid of preexisting texture
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    //Load image at specified path
    //std::cout << "[WILL] SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); PATH: " << path << std::endl;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == nullptr )
    {
        std::cout << "Unable to load image: " << path.c_str() << " ! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        //std::cout << "[OK] SDL_Surface* loadedSurface = IMG_Load( path.c_str() );" << std::endl;
        //Create texture from surface pixels
        //std::cout << "[WILL]  texture = SDL_CreateTextureFromSurface(RenderUtils::windowRenderer, loadedSurface );" << std::endl;
        texture = SDL_CreateTextureFromSurface(RenderUtils::windowRenderer, loadedSurface );
        if( texture == nullptr )
        {
            std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        else
        {
            //Get image dimensions
            //mWidth = loadedSurface->w;
            //mHeight = loadedSurface->h;
        }
        //std::cout << "[OK]  texture = SDL_CreateTextureFromSurface(RenderUtils::windowRenderer, loadedSurface );" << std::endl;

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

    spriteComponent.sourceRectangle.x = 0;
    spriteComponent.sourceRectangle.y = 0;

    if (spriteComponent.texture != nullptr){
        SDL_QueryTexture(spriteComponent.texture, nullptr, nullptr, &spriteComponent.sourceRectangle.w, &spriteComponent.sourceRectangle.h);
    } else {
        spriteComponent.sourceRectangle.h = 0;
        spriteComponent.sourceRectangle.w = 0;
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

void RenderUtils::createBlankTexture(const int width, const int height, SDL_Texture *&texture, const bool setAsTargetRenderer, Uint32 pixelFormat)
{
    //Create uninitialized texture
    texture = SDL_CreateTexture(windowRenderer, pixelFormat, SDL_TEXTUREACCESS_TARGET, width, height );
    if( texture == nullptr )
    {
        printf( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    if (setAsTargetRenderer){
        SDL_SetRenderTarget(RenderUtils::windowRenderer, texture);
    }
}


