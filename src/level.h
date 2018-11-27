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

#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <vector>
#include "tile_map.h"
#include "tile.h"
#include "sprite_sheet.h"
#include "game_object.h"

class Level : public GameObject
{
public:
    Level();

    int LoadMapTiles(TileMap _tile_map, Spritesheet spritesheet);

    void handleEvent(SDL_Event &e);
    void Draw(SDL_Rect& camera);
    void Update(std::chrono::milliseconds::rep deltaTime);

    //public variables
    std::vector<Tile> Tiles;
    TileMap tileMap;
    TextureWrapper spritesheet_texture;

    SDL_Rect camera;//todo
};

#endif // LEVEL_MANAGER_H
