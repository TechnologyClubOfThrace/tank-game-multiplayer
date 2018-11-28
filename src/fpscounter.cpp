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

#include "fpscounter.h"

FpsCounter::FpsCounter()
{
}

void FpsCounter::handleEvent(SDL_Event &e)
{

}

//SDL_GetCPUCacheLineSize
//SDL_GetCurrentVideoDriver
//SDL_GetCPUCount
//SDL_GetPlatform()
//SDL_GetVersion(v)
void FpsCounter::Draw()
{
    fps_str = (fps > 0 ? "fps: " + std::to_string(fps) : "fps: " + fps_str);

    //fps_str = fps > 0 ? (fps < 5000 ? "FPS: " + std::to_string(fps) : fps_str) : fps_str;

    /*
    fps_str = (fps > 0 ? "fps: " + std::to_string(fps) : fps_str).append(
                "\nCPU Cores: ").append(std::to_string(SDL_GetCPUCount())).append(
                "\nCPU L1 Cache line size: ").append(std::to_string(SDL_GetCPUCacheLineSize()).append(" bytes"));
                */

    texture.loadFromRenderedText(fps_str, textColor);
    texture.render(20, 20);
}

void FpsCounter::Update(std::chrono::milliseconds::rep deltaTime)
{
    fps = static_cast<int>(deltaTime > 0 ? round(1000/deltaTime) : 0);
}

void FpsCounter::LoadFont(std::string font_file_name, int ptsize )
{
    texture.font = TTF_OpenFont(font_file_name.c_str(), ptsize);
}
