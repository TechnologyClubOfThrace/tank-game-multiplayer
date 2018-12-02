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

#include "game_engine.h"
#include <SDL_image.h>
#include <thread>
#include <cmath>
#include <iostream>
#include <iterator>
#include "game.h"

GameEngine::GameEngine(int screenWidth, int screenHeight)
{
   ScreenWidth = screenWidth;
   ScreenHeight = screenHeight;
}

bool GameEngine::Init()
{
    //Initialization flag
    bool success = true;

    // (STEP 1 / 3)
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {

        // Better drawing quality
         SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);


        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "Tank Multiplayer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN );
        if( gWindow == nullptr )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            //WindowRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_SOFTWARE );
            WindowRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( WindowRenderer == nullptr )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( WindowRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            }
        } //SDL_CreateWindow

    } //Initialize SDL

    // (STEP 2 / 3)
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
    }//Initialize PNG loading

    // (STEP 3 / 3)
    //Initialize TTF
    if( TTF_Init()  < 0 )
    {
        printf( "TTF could not initialize! Error: %s\n", TTF_GetError());
        success = false;
    } else {
        fpscounter.texture.WindowRenderer = WindowRenderer;
        fpscounter.LoadFont();
    }//Initialize TTF

    Running = success;
    return success;
}

//loads the game map
bool GameEngine::LoadMap(TileMap tile_map, Spritesheet spritesheet)
{
    //set the renderer used to draw map sprites
    level.spritesheet_texture.WindowRenderer = WindowRenderer;
    int ret = level.LoadMapTiles(tile_map, spritesheet);

    return ret > 0;
}


//main game loop
void GameEngine::StartGameLoop()
{
    //frame cap related valiables
    //80 fps are ok. High fps values might produce incorrect results because of number rounding
     //IMPORTANT! For smooth movement of game objects, the fps value should be choosed based on the update frequency of
    //each object. For example if a tank object moves on the x vector 0.1 pixel / ms then choosing 60 fps will result
    //in a not smooth movement because the object position will be calculated every 16ms. So, the first time its x position
    //will be 16ms* 0.1 = round(1.6) = 2, the next will be 1.6 + 16ms*0.1 = round(1.6 + 1.6)=3 and the next will be 5 etc..
    //For slow moving objects it is better to choose an fps that will move them 1px on each update call.
    //For the above example,80fps will be much better: 12.5*0.1 = round(1.25) = 1, next: 1.25 + 1.25 = round(1.5) = 2, next: 1.5 + 1.25 = round(2.75) = 3, next: 2.75 + 1.25 = round(4) 4 etc...
    const int fps = 80;
    std::chrono::milliseconds::rep frame_delay_for_stable_fps = 1000 / fps;//the second part is how many fps we need
    std::chrono::high_resolution_clock::time_point begin_time_point = std::chrono::high_resolution_clock::now();//stores the time point before processing game objects and drawing
    deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(begin_time_point - begin_time_point).count();//stores the duration of procesing the game objects and drawing

    //enter game loop
    while (Running){

        //store the begining time point of the proccesing.
        begin_time_point = std::chrono::high_resolution_clock::now();

        HandleEvents();//process user input from keyboard/mouse/game controlers etc
        Update();//update game objects position, collitions etc
        SDL_RenderClear(WindowRenderer);
        Draw();//draw the objects on screen

        //this duration it took to process the game objects
        deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point).count();

        //frame cap.
        //If frame finished early wait for the remaining time
       if (deltaTime < frame_delay_for_stable_fps){
           //sleep for the remaining time and set the deltaTime duration again
           std::this_thread::sleep_for(std::chrono::milliseconds(frame_delay_for_stable_fps - deltaTime));
           //std::cout << "sleeping for: " << std::chrono::milliseconds(frame_delay_for_stable_fps - deltaTime).count() << std::endl;
       }
       //End of frame cap

       //display the fps counter if needed
       if (fpscounter.DisplayFpsCounter){
           deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point).count();
           fpscounter.Update(deltaTime);
           fpscounter.Draw();
           //std::cout << "deltatime: " << deltaTime << std::endl;
       }

       //display everything in screen

       SDL_RenderPresent(WindowRenderer);

       /*
       const SDL_Rect r2{50,10,50,50};
       SDL_RenderSetViewport(WindowRenderer, &r2);
       SDL_RenderPresent(WindowRenderer);
       */

       deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point).count();
    }
}
//Smooth movement
//Sluttering, delta time, frame limit, SDL_GetPerformanceCounter, SDL_GetPerformanceFrequency
//capping frame rate, accumulator
void GameEngine::HandleEvents()
{
    //loop for eny pending events
    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
             Running = false;
        }

        //call the handleEvent on each game object
        for (auto& gameObject : game::gameObjects){
            gameObject->handleEvent(e);
        }

        //A player might press the fire key and a new bullet game object
        //has to be created. It is placed in the gameObjects_for_addition vector
        //so that after returning fron the previous handleEvent call, it will be added to the
        //gameObjects vector.
        if (game::gameObjects_for_addition.size() > 0){
            std::move(game::gameObjects_for_addition.begin(), game::gameObjects_for_addition.end(), std::back_inserter(game::gameObjects));  // ##
            game::gameObjects_for_addition.clear();
        }

    }
}

void GameEngine::Update()
{
    //Calls the Update on each game object. In case an object needs to be removed
    //like for example a bullet that hits a wall, the game object is marked for removal
    //setting Exists = false. Then imidiatelly after the update call
    //the game object is removed from the gameObjects vector and its destructor is called
    //because it is a std::unique_ptr.
    //TODO: check if there is a more efficient method using remove instead of erase.
    for(auto it = game::gameObjects.begin(); it != game::gameObjects.end();)
    {
        //update game object
        //Because after calling update on each object, the object might non need to exist any more
        //it might mark itself for deletion (Exists=False), so we should remove it from the vector.
        //To remove an item from the vector while iterating it, we should follow this method,
        //using an iterator.
        (*it)->Update(deltaTime);
        if((*it)->Exists == false){
            //remove the game object if it is required
            it = game::gameObjects.erase(it);
        }else{
            ++it;
        }
    }
}

//draws the game objects
void GameEngine::Draw()
{
    //first of all draw the level as the last game object in the z-order
    //so that all other game objects are drawn on top
    level.Draw();

    //Draw all other game objects
    for (auto& gameObject : game::gameObjects){
        gameObject->Draw();
    }

    level.DrawRadar();//todo

    //if there are more than one viewports, call the draw oveload
    //on each game object with the viewport index.
    for (size_t viewPortIndex = 1; viewPortIndex <= game::gameObjects.size(); viewPortIndex++){
        for (auto& gameObject : game::gameObjects){
            gameObject->Draw(viewPortIndex);
        }
    }
}
