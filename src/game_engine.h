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

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SDL.h>
#include <chrono>

#include "scene_manager.h"
#include "render_utils.h"

//entities
#include "fps_entity.h"

//systems
#include "render_system.h"
#include "tank_input_system.h"
#include "physics_system.h"
#include "fps_system.h"


class GameEngine
{
public:
    GameEngine(int screenWidth, int screenHeight);

    //public variables
    //========================
    bool Running = false;
    //Screen dimensions
    int ScreenWidth = 0;
    int ScreenHeight = 0;
    //Event handler
    SDL_Event e;


    //public pointers
    //========================
    //The window we'll be rendering to
    SDL_Window* gWindow = nullptr;

    //public class variables
    //========================
    SceneManager sceneManager;
    FpsEntity fpsEntity;


    //public methods
    //========================
    bool Init();
    void StartGameLoop();
    void HandleEvents();
    void Update();
    void Draw();

private:
    std::chrono::milliseconds::rep deltaTime;//the time it takes to display the current frame after the previous one, in milliseconds

    //systems
    RenderSystem renderSystem;
    TankInputSystem tankInputSystem;
    PhysicsSystem physicsSystem;
    FpsSystem fpsSystem;
};

#endif // GAME_ENGINE_H
