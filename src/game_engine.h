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

#include "tile_map.h"
#include "sprite_sheet.h"
#include "tank.h"
#include "fpscounter.h"
#include <chrono>

//systems
#include "render_system.h"

class GameEngine
{
public:
    bool Running = false;

    //public variables
    //The window we'll be rendering to
    SDL_Window* gWindow = nullptr;
    //The window renderer
    SDL_Renderer* WindowRenderer = nullptr;
    Level level;

    FpsCounter fpscounter;

    //Event handler
    SDL_Event e;


    GameEngine(int screenWidth, int screenHeight);
    bool Init();
    bool LoadMap(TileMap tile_map, Spritesheet spritesheet);

    void HandleEvents();
    void Update();
    void Draw();


    void StartGameLoop();

    //Screen dimension constants
    int ScreenWidth = 0;
    int ScreenHeight = 0;
private:
    std::chrono::milliseconds::rep deltaTime;//the time it takes to display the current frame after the previous one, in milliseconds

    //systems
    RenderSystem renderSystem;
};

#endif // GAME_ENGINE_H
