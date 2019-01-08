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

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <string>
#include <iostream>
#include <sstream>
#include "pugixml.hpp"
#include "tileset.h"
#include "tile_entity.h"
#include "game.h"
#include "render_utils.h"
#include "render_system.h"
#include "viewport.h"
#include "unified_tiles_entity.h"
#include "tank_entity.h"

class SceneManager
{
public:
    SceneManager();

    TileSet tileSet;

    bool LoadFirstScene(const std::string &tmxFilePath);
    bool LoadTileset();
    bool LoadSceneEntities(pugi::xml_document &tmx_doc, const std::string &tmxFilePath);
    void SpriteRectFromTileIndex(int tile_index, std::unique_ptr<SpriteComponent> &spriteComponent);
};

#endif // SCENE_MANAGER_H
