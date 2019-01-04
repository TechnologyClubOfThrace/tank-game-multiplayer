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

void configureViewports()
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
    viewport.frame.w = ViewPort::ScreenWidth;
    viewport.frame.h = ViewPort::ScreenHeight;
    viewport.entityScale.x = 1.0;
    viewport.entityScale.y = viewport.entityScale.x;
    viewport.cameraID = 0;
    //viewport.camera.frame = viewport.frame;
    game::viewports.emplace_back(std::move(viewport));

    //Viewport 1:
    ViewPort viewport_radar;
    viewport_radar.frame.w = 150;
    viewport_radar.frame.h = 0;
    viewport_radar.frame.x = 0;
    viewport_radar.frame.y = 0;
    viewport_radar.cameraID = 1;
    viewport_radar.background_sprite_component = std::make_shared<SpriteComponent>();
    RenderUtils::LoadTextureFromFile("grey_300x200.png", *viewport_radar.background_sprite_component);
    RenderUtils::setBlendMode(viewport_radar.background_sprite_component->texture, SDL_BLENDMODE_BLEND);
    RenderUtils::setAlpha(viewport_radar.background_sprite_component->texture, 50);
    game::viewports.emplace_back(std::move(viewport_radar));
    //end of viewport configuration

    ViewPort viewport2;
    viewport2.frame.x = 0;
    viewport2.frame.y = 0;
    viewport2.frame.w = ViewPort::ScreenWidth;
    viewport2.frame.h = ViewPort::ScreenHeight;
    viewport2.entityScale.x = 1.0;
    viewport2.entityScale.y = viewport2.entityScale.x;
    viewport2.cameraID = 1;
    //viewport.camera.frame = viewport.frame;
    game::viewports.emplace_back(std::move(viewport2));
}

void configureCameras()
{
    Camera c0;
    c0.frame.x = 0;
    c0.frame.y = 0;
    c0.frame.w = game::viewports[0].frame.w;
    c0.frame.h = game::viewports[0].frame.h;
    ViewPort::allCameras.emplace_back(c0);

    Camera c1;
    c1.frame.x = 0;
    c1.frame.y = 0;
    c1.frame.w = game::viewports[1].frame.w;
    c1.frame.h = game::viewports[1].frame.h;
    ViewPort::allCameras.emplace_back(c1);
}

void configureTankEntity()
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
    ViewportTarget viewportTarget(1);
    //viewportTarget.entityScale.x = game::viewports[viewportTarget.viewportID].frame.w / static_cast<double>(GameEngine::sceneManager.levelWidth);
    //viewportTarget.entityScale.y = viewportTarget.entityScale.x;
    game::viewports[viewportTarget.viewportID].entityScale.x = game::viewports[viewportTarget.viewportID].frame.w / static_cast<double>(ViewPort::levelWidth);
    game::viewports[viewportTarget.viewportID].entityScale.y = game::viewports[viewportTarget.viewportID].entityScale.x;
    game::viewports[viewportTarget.viewportID].frame.h = static_cast<int>(std::round(game::viewports[viewportTarget.viewportID].entityScale.y * ViewPort::levelHeight));
    game::viewports[viewportTarget.viewportID].frame.x = ViewPort::ScreenWidth - game::viewports[viewportTarget.viewportID].frame.w - 20;
    game::viewports[viewportTarget.viewportID].frame.y = ViewPort::ScreenHeight - game::viewports[viewportTarget.viewportID].frame.h - 20;
    //game::viewports[viewportTarget.viewportID].camera.frame = game::viewports[viewportTarget.viewportID].frame;
    viewportTarget.destinationRectangle.w =  static_cast<int>(std::round(tank_entity->sprite_component->sourceRectangle.w * game::viewports[viewportTarget.viewportID].entityScale.x));
    viewportTarget.destinationRectangle.h =  static_cast<int>(std::round(tank_entity->sprite_component->sourceRectangle.h * game::viewports[viewportTarget.viewportID].entityScale.y));
    tank_entity->viewport_component->viewports.emplace_back(viewportTarget);

    //initial values for tank entity physics
    tank_entity->rigid_body2d_component->Acceleration.x = 0.0003;
    tank_entity->rigid_body2d_component->DirectionalForce = {3, 0};
    tank_entity->rigid_body2d_component->TorqueMagnitude = 100;
    tank_entity->rigid_body2d_component->Mass = 10000;
    tank_entity->rigid_body2d_component->Force = {0.25,0};
    tank_entity->rigid_body2d_component->AngularVelocityMaximumMagnitude = 0.06;
    tank_entity->rigid_body2d_component->AngularVelocityMagnitude = 0;
    tank_entity->rigid_body2d_component->MaxVelocityMagnitude = 0.10;
    tank_entity->rigid_body2d_component->MoI = tank_entity->rigid_body2d_component->Mass;
    tank_entity->rigid_body2d_component->AngularAccelerationMagnitude = tank_entity->rigid_body2d_component->TorqueMagnitude/tank_entity->rigid_body2d_component->MoI;
    tank_entity->rigid_body2d_component->isAccelerationfrozen = false;
    tank_entity->rigid_body2d_component->isAngularAccelerationfrozen = false;

    //insert the tank entity into the entities collection
    game::entityObjects.emplace_back(std::move(tank_entity));
}

int main()
{
    std::cout << "Begin - main()" << std::endl;

    ViewPort::ScreenWidth = 700;
    ViewPort::ScreenHeight = 700;

    //Start up SDL and create window
    if( !GameEngine::Init())
    {
        //if game engine fails to init, quit the application
        printf( "Failed to initialize!\n" );
        return 0;
    }
    std::cout << "[OK] GameEngine::Init()" << std::endl;

    //load the first level of the game from the tilemap file
    //game_engine.sceneManager.LoadFirstScene("tank_tiled_map.tmx");
    GameEngine::sceneManager.LoadFirstScene("aris-first-map.tmx");
    std::cout << "[OK] GameEngine::sceneManager.LoadFirstScene(aris-first-map.tmx)" << std::endl;

    //view ports configuration
    //The game has 2 viewports:
    //(1) the main view port and
    //(2) the radar viewport on the bottom right
    configureViewports();
    std::cout << "[OK] configureViewports();" << std::endl;

    configureCameras();

    //tank entity configuration
    configureTankEntity();
    std::cout << "[OK] configureTankEntity();" << std::endl;

    //start main game loop
    GameEngine::StartGameLoop();
    std::cout << "[OK] GameEngine::StartGameLoop();" << std::endl;

    return 0;
}
