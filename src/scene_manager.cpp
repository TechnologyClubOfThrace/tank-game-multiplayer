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

#include "scene_manager.h"

SceneManager::SceneManager()
{

}

/*
 * given the tmx file name and layer name does the following:
 * - Sets the window size
 *
 */
void SceneManager::LoadFirstScene(std::string tmxFilePath, std::string sceneLayerName)
{
    //implement a scene parser
}

/*
 * - from the map tag read the attributes: width="10" height="10" tilewidth="32" tileheight="32"
 * Multiply width*tilewidth and height*tileheight to get the world dimensions
 * - read layer with name="first-level" and
 */
