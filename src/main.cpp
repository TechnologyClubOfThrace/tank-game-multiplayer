/* ***********************************************************************
 * Tank Game Multiplayer
 * =======================================================================
 *
 * DEVELOPERS
 * (C) 2018 by Yiannis     Bourkelis  (hello@andama.org)
 * (C) 2018 by Christos    Paraskevas (cparaskevas91@gmail.com)
 * (C) 2018 by Constantine Sarmidis
 *
 * GRAPHICS
 * (C) 2018 by Aris
 *
 * SOUND
 * (C) 2018 by Panos Doukas
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
#include "render_utils.h"

#include "tank_entity.h"
#include "scene_manager.h"

using namespace std;

#undef main

void configureViewports(GameEngine &game_engine)
{
    //game viewports configuration
    //The tank game has 2 viewports;
    //1. One viewport of the main game window with a camera that follows the player tank
    //2. One viewport on the bottom right corner that displays the game map, the player tank position
    //within the map and other game objects that will be added if needed.
    //Viewport 0:
    ViewPort viewport;
    viewport.frame.x = 0;
    viewport.frame.y = 0;
    viewport.frame.w = game_engine.ScreenWidth;
    viewport.frame.h = game_engine.ScreenHeight;
    viewport.camera.frame = viewport.frame;
    game::viewports.emplace_back(viewport);
    //Viewport 1:
    ViewPort viewport_radar;
    viewport_radar.frame.w = 150;
    viewport_radar.frame.h = 0;
    viewport_radar.frame.x = 0;
    viewport_radar.frame.y = 0;
    game::viewports.emplace_back(viewport_radar);
    //end of viewport configuration
}

void configureTankEntity(GameEngine &game_engine)
{
    //tank entity configuration

    //first of all setup initial position and
    //sprite that includes the tank image
    auto tank_entity = std::make_unique<TankEntity>();
    tank_entity->transform_component->Position.x = 100;
    tank_entity->transform_component->Position.y = 100;
    RenderUtils::LoadTextureFromFile("tank_133x50.png", *tank_entity->sprite_component);
    tank_entity->transform_component->RotationAngleDegrees = 0;

    //configuration of the radar viewport
    //The viewport dimensions (width,height) are relative to the
    //level dimensions, scaled down.
    //Everything drawn inside the viewport is scaled down.
    tank_entity->viewport_component->entityScale.x =  game::viewports[tank_entity->viewport_component->viewportID].frame.w / static_cast<double>(game_engine.ScreenWidth);
    tank_entity->viewport_component->entityScale.y = tank_entity->viewport_component->entityScale.x;
    game::viewports[tank_entity->viewport_component->viewportID].frame.h = static_cast<int>(std::round(tank_entity->viewport_component->entityScale.y * game_engine.ScreenHeight));
    game::viewports[tank_entity->viewport_component->viewportID].frame.x = game_engine.ScreenWidth - game::viewports[tank_entity->viewport_component->viewportID].frame.w - 100;
    game::viewports[tank_entity->viewport_component->viewportID].frame.y = game_engine.ScreenHeight - game::viewports[tank_entity->viewport_component->viewportID].frame.h - 100;
    game::viewports[tank_entity->viewport_component->viewportID].camera.frame = game::viewports[tank_entity->viewport_component->viewportID].frame;
    tank_entity->viewport_component->destinationRectangle.w =  static_cast<int>(std::round(tank_entity->sprite_component->sourceRectangle.w * tank_entity->viewport_component->entityScale.x));
    tank_entity->viewport_component->destinationRectangle.h =  static_cast<int>(std::round(tank_entity->sprite_component->sourceRectangle.h * tank_entity->viewport_component->entityScale.y));

    //initial values for tank entity physics
    tank_entity->rigid_body2d_component->Acceleration.x = 0.000;
    tank_entity->rigid_body2d_component->Force = {0, 0};
    tank_entity->rigid_body2d_component->TorqueMagnitude = 000;
    tank_entity->rigid_body2d_component->Mass = 10000;
    tank_entity->rigid_body2d_component->AngularVelocityMaximumMagnitude = 0.06;
    tank_entity->rigid_body2d_component->AngularVelocityMagnitude = 0;
    tank_entity->rigid_body2d_component->VelocityMaximumMagnitude = 0.10;
    tank_entity->rigid_body2d_component->MoI = tank_entity->rigid_body2d_component->Mass;
    tank_entity->rigid_body2d_component->AngularAccelerationMagnitude = tank_entity->rigid_body2d_component->TorqueMagnitude/tank_entity->rigid_body2d_component->MoI;
    tank_entity->rigid_body2d_component->isAccelerationfrozen = false;
    tank_entity->rigid_body2d_component->isAngularAccelerationfrozen = false;

    game::entityObjects.emplace_back(std::move(tank_entity));
}

int main()
{
    GameEngine game_engine(700,600);
    //Start up SDL and create window
    if( !game_engine.Init())
    {
        //if game engine fails to init, quit the application
        printf( "Failed to initialize!\n" );
        return 0;
    }

    //load the first level of the game from the tilemap file
    //game_engine.sceneManager.LoadFirstScene("tank_tiled_map.tmx");
    game_engine.sceneManager.LoadFirstScene("aris-first-map.tmx");

    //view ports configuration
    //The game has 2 viewports:
    //(1) the main view port and
    //(2) the radar viewport on the bottom right
    configureViewports(game_engine);

    //tank entity configuration
    configureTankEntity(game_engine);

    //start main game loop
    game_engine.StartGameLoop();
}
