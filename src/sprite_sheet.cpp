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

#include "sprite_sheet.h"

Spritesheet::Spritesheet()
{
}

//a somehow smart way to get the related sprite x and y
//based in the index it has inside the spritesheet
void Spritesheet::SpriteFromIndex(int sprite_index, Sprite &sprite)
{
    auto res = std::div(sprite_index, columns);

    sprite.rect.x = res.rem * sprite_width;
    sprite.rect.y = res.quot * sprite_height;
    sprite.index = sprite_index;
}

/*
0 (x=0,  y=0) 0, 0
1 (x=32, y=0) 0, 1
2 (x=64, y=0) 0, 2
3 (x=0,  y=32) 1, 0
4 (x=32, y=32) 1, 1
5 (x=64, y=32) 1, 2
*/
