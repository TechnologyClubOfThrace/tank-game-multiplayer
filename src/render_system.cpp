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

void RenderSystem::RenderInViewport(TransformComponent &transformComponent, SpriteComponent &spriteComponent, ViewportTarget &viewportTarget, const ViewPort& viewport)
{
    SDL_Rect destinationRectangle {
                static_cast<int>(round(viewport.frame.x + (transformComponent.Position.x * viewport.entityScale.x) - ViewPort::allCameras[viewport.cameraID].frame.x)),
                static_cast<int>(round(viewport.frame.y + (transformComponent.Position.y * viewport.entityScale.y) - ViewPort::allCameras[viewport.cameraID].frame.y)),
                static_cast<int>(round(spriteComponent.sourceRectangle.w * viewport.entityScale.x)),
                static_cast<int>(round(spriteComponent.sourceRectangle.h * viewport.entityScale.y))
    };

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

/*
void RenderSystem::RenderInViewport2(TransformComponent &transformComponent, SpriteComponent &spriteComponent, ViewportTarget &viewportTarget, const ViewPort& viewport)
{
    //viewportComponent.destinationRectangle.x = static_cast<int>(round((transformComponent.Position.x * viewportComponent.entityScale.x) + static_cast<double>(viewport.camera.frame.x)));
    //viewportComponent.destinationRectangle.y = static_cast<int>(round((transformComponent.Position.y * viewportComponent.entityScale.y) + static_cast<double>(viewport.camera.frame.y)));

    if (viewportTarget.entityScale.x == 1.0 && viewportTarget.entityScale.y == 1.0){
        if (!spriteComponent.renderPositionRelatedToCamera){
            //spriteComponent.destinationRectangle.x = static_cast<int>(round(transformComponent.Position.x - static_cast<double>(viewports[0].camera.frame.x)));
            //spriteComponent.destinationRectangle.y = static_cast<int>(round(transformComponent.Position.y - static_cast<double>(viewports[0].camera.frame.y)));
            spriteComponent.destinationRectangle.x = static_cast<int>((transformComponent.Position.x - (viewport.camera.frame.x)));
            spriteComponent.destinationRectangle.y = static_cast<int>((transformComponent.Position.y - (viewport.camera.frame.y)));
        }

        SDL_RenderCopyEx(RenderUtils::windowRenderer,
                         spriteComponent.texture,
                         &spriteComponent.sourceRectangle,//source rectangle
                         &spriteComponent.destinationRectangle,//destination rectangle
                         transformComponent.RotationAngleDegrees,//angle
                         nullptr,//center
                         SDL_RendererFlip::SDL_FLIP_NONE
                    );
    } else {
        viewportTarget.destinationRectangle.x = static_cast<int>(((transformComponent.Position.x * viewportTarget.entityScale.x) + static_cast<double>(viewport.camera.frame.x)));
        viewportTarget.destinationRectangle.y = static_cast<int>(((transformComponent.Position.y * viewportTarget.entityScale.y) + static_cast<double>(viewport.camera.frame.y)));


        SDL_RenderCopyEx(RenderUtils::windowRenderer,
                         spriteComponent.texture,
                         &spriteComponent.sourceRectangle,//source rectangle
                         &viewportTarget.destinationRectangle,//destination rectangle
                         transformComponent.RotationAngleDegrees,//angle
                         nullptr,//center
                         SDL_RendererFlip::SDL_FLIP_NONE
                    );
    }

   // std::cout << "res: " << res << " ,sprite w: " << spriteComponent.rect.w << std::endl;
}
*/

void RenderSystem::RenderViewportSprite(SpriteComponent &spriteComponent, ViewPort &viewport)
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
