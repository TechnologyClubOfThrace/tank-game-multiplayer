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

#include "level.h"
#include <fstream>

Level::Level()
{

}

//loads the map tiles
int Level::LoadMapTiles(const TileMap &_tile_map, Spritesheet &spritesheet)
{
    tileMap = _tile_map;

    //the texture that contains all the map building blocks (sprites)
    spritesheet_texture.loadFromFile(spritesheet.file_name);

    //Success flag
    bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map(tileMap.file_name);

    //If the map couldn't be loaded
    if( !map )
    {
        printf( "Unable to load map file!\n" );
        tilesLoaded = false;
    }
    else
    {
        //Initialize the tiles
        for( int i = 0; i < tileMap.total_tiles; ++i )
        {
            //Determines what kind of tile will be made
            int tileType = -1;

            //Read tile from map file
            map >> tileType;

            //If the was a problem in reading the map
            if( map.fail() )
            {
                //Stop loading map
                printf( "Error loading map: Unexpected end of file!\n" );
                tilesLoaded = false;
                break;
            }

            //If the number is a valid tile number
            if( ( tileType >= 0 ) && ( tileType < spritesheet.total_sprites ) )
            {
                //create a tile with the location it should exist inside the game level
                //and the related sprite
                Tile tile(x, y, spritesheet.sprite_width, spritesheet.sprite_height);
                tile.sprite.rect.w = spritesheet.sprite_width;
                tile.sprite.rect.h = spritesheet.sprite_height;
                tile.sprite.spritesheet_texture = &spritesheet_texture;
                spritesheet.SpriteFromIndex(tileType, tile.sprite);
                Tiles.emplace_back(tile);
            }
            //If we don't recognize the tile type
            else
            {
                //Stop loading map
                printf( "Error loading map: Invalid tile type at %d!\n", i );
                tilesLoaded = false;
                break;
            }

            //Move to next tile spot
            x += spritesheet.sprite_height;

            //If we've gone too far
            if( x >= tileMap.level_width )
            {
                //Move back
                x = 0;

                //Move to the next row
                y += spritesheet.sprite_width;
            }
        }
    }

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

void Level::handleEvent(SDL_Event &e)
{

}

void Level::Draw()
{
    //render all map tiles
    for (auto& v : Tiles){
        v.render();
    }
}

void Level::DrawRadar()
{
    //render all map tiles
    for (auto& v : Tiles){
        v.render_radar();
    }
}

void Level::Update(std::chrono::milliseconds::rep deltaTime)
{

}
