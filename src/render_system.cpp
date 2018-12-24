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
    if (!spriteComponent.renderPositionRelatedToCamera){
        //spriteComponent.destinationRectangle.x = static_cast<int>(round(transformComponent.Position.x - static_cast<double>(viewports[0].camera.frame.x)));
        //spriteComponent.destinationRectangle.y = static_cast<int>(round(transformComponent.Position.y - static_cast<double>(viewports[0].camera.frame.y)));
        spriteComponent.destinationRectangle.x = static_cast<int>((transformComponent.Position.x - (viewports[0].camera.frame.x)));
        spriteComponent.destinationRectangle.y = static_cast<int>((transformComponent.Position.y - (viewports[0].camera.frame.y)));
    }

    //std::cout << "render x: " << spriteComponent.destinationRectangle.x << " , render y: " << spriteComponent.destinationRectangle.y << std::endl;
    //SDL_SetTextureBlendMode(spriteComponent.texture, SDL_BLENDMODE_BLEND);

    SDL_RenderCopyEx(RenderUtils::windowRenderer,
                     spriteComponent.texture,
                     &spriteComponent.sourceRectangle,//source rectangle
                     &spriteComponent.destinationRectangle,//destination rectangle
                     transformComponent.RotationAngleDegrees,//angle
                     nullptr,//center
                     SDL_RendererFlip::SDL_FLIP_NONE
                );

   // std::cout << "res: " << res << " ,sprite w: " << spriteComponent.rect.w << std::endl;
}

void RenderSystem::RenderInViewport(TransformComponent &transformComponent, SpriteComponent &spriteComponent, ViewportComponent &viewportComponent,  ViewPort &viewport)
{
    //viewportComponent.destinationRectangle.x = static_cast<int>(round((transformComponent.Position.x * viewportComponent.entityScale.x) + static_cast<double>(viewport.camera.frame.x)));
    //viewportComponent.destinationRectangle.y = static_cast<int>(round((transformComponent.Position.y * viewportComponent.entityScale.y) + static_cast<double>(viewport.camera.frame.y)));
    viewportComponent.destinationRectangle.x = static_cast<int>(((transformComponent.Position.x * viewportComponent.entityScale.x) + static_cast<double>(viewport.camera.frame.x)));
    viewportComponent.destinationRectangle.y = static_cast<int>(((transformComponent.Position.y * viewportComponent.entityScale.y) + static_cast<double>(viewport.camera.frame.y)));


    SDL_RenderCopyEx(RenderUtils::windowRenderer,
                     spriteComponent.texture,
                     &spriteComponent.sourceRectangle,//source rectangle
                     &viewportComponent.destinationRectangle,//destination rectangle
                     transformComponent.RotationAngleDegrees,//angle
                     nullptr,//center
                     SDL_RendererFlip::SDL_FLIP_NONE
                );

   // std::cout << "res: " << res << " ,sprite w: " << spriteComponent.rect.w << std::endl;
}
