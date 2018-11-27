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

#include <iostream>
#include <memory>
#include "game_engine.h"
#include "game_objects.h"

using namespace std;

int main()
{
    GameEngine game_engine(864,608);
    //Start up SDL and create window
    if( !game_engine.Init())
    {
        printf( "Failed to initialize!\n" );
        return 0;
    }

    //Object with information about the game map
    TileMap tile_map;
    tile_map.level_width = 864;  //640; // <<<<<<<<<<< //Level width
    tile_map.level_height = 608;  //480;
    tile_map.file_name = "map96.txt"; //The file that contains the map
    tile_map.total_tiles = 513;  //300; // <<<<<<<<<<< //The total number of tiles inside the map


    //Object that holds info about the spritesheet containing
    //the sprites that we use to design the level base on the previous tile map
    Spritesheet spritesheet;
    spritesheet.file_name = "snake-tileset_no_trans.png";
    spritesheet.sprite_height = 32;
    spritesheet.sprite_width = 32;
    spritesheet.total_sprites = 9;//how many sprites the image contains
    //sprites are organized inside the image file in columns and rows.
    //that way we can later calculate the exact position to draw each sprite based on the lacation it has inside the tile map.
    spritesheet.columns = 3;
    spritesheet.rows = 3;

    //load the game map
    game_engine.LoadMap(tile_map, spritesheet);

    //load the tank object in our level
    auto snake =  std::make_unique<Snake>();
    snake->snakeTexture.WindowRenderer = game_engine.WindowRenderer;
    //snake->snakeTexture.loadFromFile("snake_32x32.png");
    snake->snakeTexture.loadFromFile("tank_133x50.png");
    snake->level = &game_engine.level;
    GameObjects::gameObjects.emplace_back(std::move(snake));

    /*
    //load the tank object in our level
    std::unique_ptr<Snake> snake2(new Snake);
    snake2->Position.y += 100;
    snake2->snakeTexture.WindowRenderer = game_engine.WindowRenderer;
    //snake->snakeTexture.loadFromFile("snake_32x32.png");
    snake2->snakeTexture.loadFromFile("tank_133x50.png");
    snake2->level = &game_engine.level;
    GameObjects::gameObjects.emplace_back(std::move(snake2));

    //load the tank object in our level
    std::unique_ptr<Snake> snake3(new Snake);
    snake3->Position.y += 200;
    snake3->snakeTexture.WindowRenderer = game_engine.WindowRenderer;
    //snake->snakeTexture.loadFromFile("snake_32x32.png");
    snake3->snakeTexture.loadFromFile("tank_133x50.png");
    snake3->level = &game_engine.level;
    GameObjects::gameObjects.emplace_back(std::move(snake3));


    //load the tank object in our level
    std::unique_ptr<Snake> snake4(new Snake);
    snake4->Position.y += 300;
    snake4->snakeTexture.WindowRenderer = game_engine.WindowRenderer;
    //snake->snakeTexture.loadFromFile("snake_32x32.png");
    snake4->snakeTexture.loadFromFile("tank_133x50.png");
    snake4->level = &game_engine.level;
    GameObjects::gameObjects.emplace_back(std::move(snake4));
    */

    //start main game loop
    game_engine.StartGameLoop();
}
