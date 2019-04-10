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
 * This function loads the first level from the tilemap file.
 * The first level should be named "Level-1"
 * Also, it loads various attributes required for the game startup:
 * - The width and size of the scene
 * - The total number of tiles horizontaly and verticaly
 * - The width and height of each tile
 * - The tileset filename
 */
bool SceneManager::LoadFirstScene(const std::string &tmxFilePath)
{
    std::cout << "[ENTERED] SceneManager::LoadFirstScene(const std::string &tmxFilePath)" << std::endl;
    //Load the tilemap xml file
    pugi::xml_document tmx_doc;
    pugi::xml_parse_result result = tmx_doc.load_file(tmxFilePath.c_str());
    if (!result) {
        std::cerr << "Could not load tilemap xml file in path: " << tmxFilePath << std::endl;
        return false;
    }
    std::cout << "[OK] tmx_doc.load_file(tmxFilePath.c_str());" << std::endl;

    //read map info
    int level_width_tiles_count = tmx_doc.child("map").attribute("width").as_int(); //total number of tiles verticaly
    int level_height_tiles_count = tmx_doc.child("map").attribute("height").as_int(); //total number of tiles horizontaly
    tileSet.tileWidth = tmx_doc.child("map").attribute("tilewidth").as_int();
    tileSet.tileHeight = tmx_doc.child("map").attribute("tileheight").as_int();
    std::cout << "[OK] read map info" << std::endl;

    ViewPort::levelWidth = level_width_tiles_count * tileSet.tileWidth;
    ViewPort::levelHeight = level_height_tiles_count * tileSet.tileHeight;

    //read tileset .tsx filename
    //and load tileset texture.
    //In case of error in tileset loading
    //stop scene processing and return false;
    tileSet.tsx_fileName = tmx_doc.child("map").child("tileset").attribute("source").as_string();
    std::cout << "[OK] read tsx_fileName" << std::endl;

    if (!LoadTileset()) return false;
    std::cout << "[OK] LoadTileset" << std::endl;
    if (!LoadSceneEntities(tmx_doc, tmxFilePath)) return false;
    std::cout << "[OK] LoadSceneEntities" << std::endl;

    return true;
}

bool SceneManager::LoadTileset()
{
     std::cout << "[ENTERED] LoadTileset" << std::endl;
     std::cout << "[ENTERED] WILL OPEN XML: " << tileSet.tsx_fileName << std::endl;
    //Load the tilemap xml file
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(tileSet.tsx_fileName.c_str());
    if (!result) {
        std::cerr << "Could not load tileset xml file in path: " << tileSet.tsx_fileName << std::endl;
        return false;
    }
    std::cout << "[OK] doc.load_file(tileSet.tsx_fileName.c_str());" << std::endl;


    tileSet.spacing = doc.child("tileset").attribute("spacing").as_int();
    tileSet.tileCount = doc.child("tileset").attribute("tilecount").as_int();
    tileSet.columns = doc.child("tileset").attribute("columns").as_int();
    tileSet.image_fileName = doc.child("tileset").child("image").attribute("source").as_string();
    std::cout << "[OK] READ TILESET INFO FROM XML" << std::endl;

    std::cout << "[WILL] RenderUtils::LoadTextureFromFile(tileSet.image_fileName, tileSet.texture); FILENAME: " << tileSet.image_fileName << std::endl;
    return RenderUtils::LoadTextureFromFile(tileSet.image_fileName, tileSet.texture);
}

bool SceneManager::LoadSceneEntities(pugi::xml_document &tmx_doc, const std::string &tmxFilePath)
{
    //check if first level exist in the file
    if (std::string(tmx_doc.child("map").child("layer").attribute("name").as_string()) != "Level-1"){
        std::cerr << "First scene (Level-1) does not exist in the tilemap xml file." << tmxFilePath << std::endl;
        return false;
    }

    //init the UnifiedTilesEntity. We will copy (unify) all the map tiles into
    //the one texture of the UnifiedTilesEntity's sprite_component
    auto unifiedTilesEntity = std::make_unique<UnifiedTilesEntity>();
    Uint32 pixelFormat;
    SDL_QueryTexture(tileSet.texture, &pixelFormat, nullptr, nullptr, nullptr);
    RenderUtils::createBlankTexture(static_cast<int>(ViewPort::levelWidth), static_cast<int>(ViewPort::levelHeight), unifiedTilesEntity->sprite_component->texture, true, pixelFormat);
    unifiedTilesEntity->sprite_component->sourceRectangle.w = static_cast<int>(ViewPort::levelWidth);
    unifiedTilesEntity->sprite_component->sourceRectangle.h = static_cast<int>(ViewPort::levelHeight);

    //first level exist. Read map data
     std::string level_map_data(tmx_doc.child("map").child("layer").child("data").text().as_string());
     std::stringstream ss(level_map_data);
     int row, col = 0;
     while (ss.good()){
         std::string map_line;
         std::getline(ss, map_line, '\n' );

         if(!map_line.empty()){
            row = 0;
            std::stringstream map_line_ss(map_line);
            while (map_line_ss.good()){
                std::string tile_index;
                std::getline(map_line_ss, tile_index, ',');
                if(!tile_index.empty()){
                    int tile_index_number = std::stoi(tile_index);
                    auto tileEntity = std::make_unique<TileEntity>();

                    tileEntity->sprite_component->texture = tileSet.texture;
                    SpriteRectFromTileIndex(tile_index_number, tileEntity->sprite_component);
                    tileEntity->transform_component->Position.x = row * tileSet.tileWidth;
                    tileEntity->transform_component->Position.y = col * tileSet.tileHeight;
                    //game::entityObjects.emplace_back(std::move(tileEntity));


                    ViewPort viewport;
                    viewport.frame.x = 0;
                    viewport.frame.y = 0;
                    viewport.frame.w = static_cast<int>(ViewPort::levelWidth);
                    viewport.frame.h = static_cast<int>(ViewPort::levelHeight);


                    RenderSystem::RenderInViewport(*tileEntity->transform_component,
                                                   *tileEntity->sprite_component,
                                                   tileEntity->target_viewport_component->target_viewports[0],
                                                   viewport);

                    row++;
                }
            }
            col++;
         }
     }



    unifiedTilesEntity->collider2d_collection_component = std::make_unique<Collider2DCollectionComponent>();
    unifiedTilesEntity->collider2d_collection_component->allowsCollisionCheck = true;

    Rectangle2D rect2d(0,-100,ViewPort::levelWidth,110);
    auto recttop = std::make_unique<RectangleCollider2D>(rect2d, CollisionRespose::NoResponse);
    unifiedTilesEntity->collider2d_collection_component->colliders.emplace_back(std::move(recttop));

    Rectangle2D rect2d_left(-100,0,162,ViewPort::levelHeight);
    auto rectleft = std::make_unique<RectangleCollider2D>(rect2d_left, CollisionRespose::NoResponse);
    unifiedTilesEntity->collider2d_collection_component->colliders.emplace_back(std::move(rectleft));

    Rectangle2D rect2d_right(ViewPort::levelWidth-10,0,100,ViewPort::levelHeight);
    auto rectright = std::make_unique<RectangleCollider2D>(rect2d_right, CollisionRespose::NoResponse);
    unifiedTilesEntity->collider2d_collection_component->colliders.emplace_back(std::move(rectright));

    Rectangle2D rect2d_bottom(0,ViewPort::levelHeight-10,ViewPort::levelWidth,100);
    auto rectbottom = std::make_unique<RectangleCollider2D>(rect2d_bottom, CollisionRespose::NoResponse);
    unifiedTilesEntity->collider2d_collection_component->colliders.emplace_back(std::move(rectbottom));

    game::entityObjects.emplace_back(std::move(unifiedTilesEntity));
    //Reset render target
    SDL_SetRenderTarget(RenderUtils::windowRenderer, nullptr);


    return true;
}

//a somehow smart way to get the related sprite x and y
//based in the index it has inside the spritesheet
void SceneManager::SpriteRectFromTileIndex(int tile_index, std::unique_ptr<SpriteComponent> &spriteComponent)
{
    auto res = std::div(tile_index-1, tileSet.columns);

    spriteComponent->sourceRectangle.x = tileSet.spacing + res.rem * tileSet.tileWidth + (res.rem * tileSet.spacing);
    spriteComponent->sourceRectangle.y = tileSet.spacing + res.quot * tileSet.tileHeight + (res.quot * tileSet.spacing);
    spriteComponent->sourceRectangle.w = tileSet.tileWidth;
    spriteComponent->sourceRectangle.h = tileSet.tileHeight;
}

/*
0 (x=0,  y=0) 0, 0
1 (x=32, y=0) 0, 1
2 (x=64, y=0) 0, 2
3 (x=0,  y=32) 1, 0
4 (x=32, y=32) 1, 1
5 (x=64, y=32) 1, 2
*/

/*
 * - from the map tag read the attributes: width="10" height="10" tilewidth="32" tileheight="32"
 * Multiply width*tilewidth and height*tileheight to get the world dimensions
 * - read layer with name="first-level" and
 */
