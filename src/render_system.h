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

#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "transform_component.h"
#include "sprite_component.h"
#include "viewport.h"

class RenderSystem
{
public:
    RenderSystem();
    void Render(TransformComponent &transformComponent, SpriteComponent &spriteComponent, std::vector<ViewPort> &viewports);
    static bool CreateTextureFromFile(std::string path, SDL_Renderer *renderer, SpriteComponent &spriteComponent);

    SDL_Renderer * renderer;
};

#endif // RENDER_SYSTEM_H
