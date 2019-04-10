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

void RenderSystem::RenderInViewport(const TransformComponent &transformComponent, const SpriteComponent &spriteComponent, const TargetViewport &targetViewport, const ViewPort& viewport)
{
    double x = static_cast<double>(viewport.frame.x) + (transformComponent.Position.x * viewport.entityScale.x) - (ViewPort::allCameras[viewport.cameraID].frame.getX());
    double y = static_cast<double>(viewport.frame.y) + (transformComponent.Position.y * viewport.entityScale.y) - ViewPort::allCameras[viewport.cameraID].frame.getY();
    //std::cout << "x=" << x << " ,y=" << y << std::endl;
    SDL_Rect destinationRectangle {
                static_cast<int>(round(x)),
                static_cast<int>(round(y)),
                static_cast<int>(ceil(static_cast<double>(spriteComponent.sourceRectangle.w) * transformComponent.Scale.x * targetViewport.EntityScale.x * viewport.entityScale.x)),
                static_cast<int>(ceil(static_cast<double>(spriteComponent.sourceRectangle.h) * transformComponent.Scale.y * targetViewport.EntityScale.y * viewport.entityScale.y))
    };

    //if (SDL_HasIntersection(&viewport.frame, &destinationRectangle) == SDL_FALSE){
    //    return;
    //}

    //todo: SDL added batching support. should check when it is available because it will improve rendering performance
    //auto batching = SDL_GetHintBoolean(SDL_HINT_RENDER_BATCHING, SDL_TRUE);
    SDL_RenderSetClipRect(RenderUtils::windowRenderer, &viewport.frame);

    SDL_RenderCopyEx(RenderUtils::windowRenderer,
                     spriteComponent.texture,
                     &spriteComponent.sourceRectangle,//source rectangle
                     &destinationRectangle,//destination rectangle
                     transformComponent.RotationAngleDegrees,//angle
                     nullptr,//center
                     SDL_RendererFlip::SDL_FLIP_NONE
                );
}

void RenderSystem::RenderViewportSprite(const SpriteComponent &spriteComponent, const ViewPort &viewport)
{
    SDL_RenderCopyEx(RenderUtils::windowRenderer,
                     spriteComponent.texture,
                     &spriteComponent.sourceRectangle,//source rectangle
                     &viewport.frame,//destination rectangle
                     0,//angle
                     nullptr,//center
                     SDL_RendererFlip::SDL_FLIP_NONE
                );

   // std::cout << "res: " << res << " ,sprite w: " << spriteComponent.rect.w << std::endl;
}
