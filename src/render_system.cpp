/* ***********************************************************************
 * Tank Game Multiplayer
 * (C) 2018 by Yiannis     Bourkelis  (hello@andama.org)
 * (C) 2018 by Christos    Paraskevas (cparaskevas91@gmail.com)
 * (C) 2018 by Constantine Sarmidis   (hello@andama.org)
 *
 * This file is part of Tank Game Multiplayer.
 *
 * Tank Game Multiplayer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tank Game Multiplayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tank Game Multiplayer.  If not, see <http://www.gnu.org/licenses/>.
 * ***********************************************************************/

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
                     transformComponent.RotationAngleDegrees,//angle
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
