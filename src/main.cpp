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
#include "game.h"

#include "tank_entity.h"

using namespace std;

#undef main

int main()
{
    GameEngine game_engine(400,400);
    //Start up SDL and create window
    if( !game_engine.Init())
    {
        printf( "Failed to initialize!\n" );
        return 0;
    }

    //game viewports configuration
    //The tank game has 2 viewports;
    //1. One viewport of the main game window with a camera that follows the player tank
    //2. One viewport on the bottom right corner that displays the game map, the player tank position
    //within the map and other game objects that will be added if needed.
    //Viewport 1:
    ViewPort viewport;
    viewport.frame.x = 0;
    viewport.frame.y = 0;
    viewport.frame.w = game_engine.ScreenWidth;
    viewport.frame.h = game_engine.ScreenHeight;
    viewport.camera.frame = viewport.frame;
    game::viewports.emplace_back(viewport);
    //Viewport 2:
    ViewPort viewport_radar;
    viewport_radar.frame.x = 290;
    viewport_radar.frame.y = 290;
    viewport_radar.frame.w = 86;
    viewport_radar.frame.h = 61;
    viewport_radar.camera.frame = viewport_radar.frame;
    game::viewports.emplace_back(viewport_radar);
    //Viewport 3:
    ViewPort viewport_radar2;
    viewport_radar2.frame.x = 20;
    viewport_radar2.frame.y = 290;
    viewport_radar2.frame.w = 86;
    viewport_radar2.frame.h = 61;
    viewport_radar2.camera.frame = viewport_radar2.frame;
    game::viewports.emplace_back(viewport_radar2);
    //end of viewport configuration

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
    auto tank =  std::make_unique<Tank>();
    tank->texture.WindowRenderer = game_engine.WindowRenderer;
    //snake->snakeTexture.loadFromFile("snake_32x32.png");
    tank->texture.loadFromFile("tank_133x50.png");
    tank->level = &game_engine.level;
    game::gameObjects.emplace_back(std::move(tank));

    auto tank_entity = std::make_unique<TankEntity>();
    tank_entity->transform_component = std::make_unique<TransformComponent>();
    tank_entity->transform_component->Position.x = 100;
    tank_entity->transform_component->Position.y = 100;
    tank_entity->hasTransformComponent = true;
    tank_entity->sprite_component = std::make_unique<SpriteComponent>();
    tank_entity->hasSpriteComponent = true;
    RenderSystem::CreateTextureFromFile("tank_133x50.png",
                                        game_engine.WindowRenderer,
                                        *tank_entity->sprite_component);
    tank_entity->tank_input_component = std::make_unique<TankInputComponent>();
    tank_entity->hasTankInputComponent = true;
    tank_entity->rigid_body2d_component = std::make_unique<RigidBody2DComponent>();
    tank_entity->hasRigidBody2DComponent = true;
    tank_entity->rigid_body2d_component->Mass = 10000;

    game::entityObjects.emplace_back(std::move(tank_entity));

    //start main game loop
    game_engine.StartGameLoop();
}
