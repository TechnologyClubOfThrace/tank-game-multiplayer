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

#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <SDL.h>
#include <memory>

enum class TexturePointerHandler {
    FreeTextureOnDestructor,
    KeepTexturePointer
};

class SpriteComponent
{
public:
    SpriteComponent();
    SpriteComponent(TexturePointerHandler texturePointerHandler);
    ~SpriteComponent();

    SDL_Rect sourceRectangle {};//initial texture size. Set on texture load.
    SDL_Texture * texture = nullptr;
    TexturePointerHandler texturePointerHandler;

private:
    void FreeTextureMemory();
};

#endif // SPRITE_COMPONENT_H
