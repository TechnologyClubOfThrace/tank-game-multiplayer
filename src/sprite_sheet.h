/* ***********************************************************************
 * Tank Game Multiplayer
 * (C) 2018 by Yiannis Bourkelis (hello@andama.org)
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

#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <string>
#include "sprite.h"

class Spritesheet
{
public:
    Spritesheet();

    std::string file_name = "";//the map file path. It contains the position and type of each tile.
    int total_sprites = 0; //the total number of sprites inside the Spritesheet image file.
    int columns = 0;
    int rows = 0;
    int sprite_width = 0;
    int sprite_height = 0;

    void SpriteFromIndex(int sprite_index, Sprite& sprite);
};

#endif // SPRITE_SHEET_H
