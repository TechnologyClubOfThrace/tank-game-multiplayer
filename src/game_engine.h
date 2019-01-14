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
#include "zoom_input_system.h"
#include "physics_system.h"
#include "fps_system.h"

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#endif

class GameEngine
{
public:
    GameEngine();

    //public variables
    //========================
    static bool Running;

    //Event handler
    static SDL_Event e;


    //public pointers
    //========================
    //The window we'll be rendering to
    static SDL_Window* gWindow;

    //public class variables
    //========================
    static SceneManager sceneManager;
    static FpsEntity fpsEntity;


    //public methods
    //========================
    static bool Init();
    static void StartGameLoop();
    static void HandleEvents();
    static void Update();
    static void Draw();
    static void game_engine_one_iteration();
    static void game_engine_infinite_loop();
    static void game_engine_infinite_loop2();

    static void DisplayEnvironmentInfo();
private:
    //systems
    static TankInputSystem tankInputSystem;
    static PhysicsSystem physicsSystem;
    static FpsSystem fpsSystem;

    //frame cap related valiables
    //80 fps are ok. High fps values might produce incorrect results because of number rounding
     //IMPORTANT! For smooth movement of game objects, the fps value should be choosed based on the update frequency of
    //each object. For example if a tank object moves on the x vector 0.1 pixel / ms then choosing 60 fps will result
    //in a not smooth movement because the object position will be calculated every 16ms. So, the first time its x position
    //will be 16ms* 0.1 = round(1.6) = 2, the next will be 1.6 + 16ms*0.1 = round(1.6 + 1.6)=3 and the next will be 5 etc..
    //For slow moving objects it is better to choose an fps that will move them 1px on each update call.
    //For the above example,80fps will be much better: 12.5*0.1 = round(1.25) = 1, next: 1.25 + 1.25 = round(1.5) = 2, next: 1.5 + 1.25 = round(2.75) = 3, next: 2.75 + 1.25 = round(4) 4 etc...
    static int fps;
    static std::chrono::milliseconds::rep frame_delay_for_stable_fps;//the second part is how many fps we need
    static std::chrono::high_resolution_clock::time_point begin_time_point;//stores the time point before processing game objects and drawing
    static std::chrono::milliseconds::rep deltaTime;
    //the time it takes to display the current frame after the previous one, in milliseconds

    static int max_fps_ticks;
    static int fps_ticks;
};

#endif // GAME_ENGINE_H
