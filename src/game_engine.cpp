/* ***********************************************************************
 * Tank Game Multiplayer
 * (C) 2018 by Yiannis     Bourkelis  (hello@andama.org)
 * (C) 2018 by Christos    Paraskevas (cparaskevas91@gmail.com)
 * (C) 2018 by Constantine Sarmidis   (hello@andama.org)
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
#include "entity.h"


//public variables
//========================
bool GameEngine::Running = false;

//Event handler
SDL_Event GameEngine::e;

//public pointers
//========================
//The window we'll be rendering to
SDL_Window* GameEngine::gWindow = nullptr;

//public class variables
//========================
SceneManager GameEngine::sceneManager;
FpsEntity GameEngine::fpsEntity;

// ======= PRIVATE =======
//systems
RenderSystem GameEngine::renderSystem;
TankInputSystem GameEngine::tankInputSystem;
PhysicsSystem GameEngine::physicsSystem;
FpsSystem GameEngine::fpsSystem;

// ======= FRAME CAPPING RELATED =======
int GameEngine::fps = 70;
std::chrono::milliseconds::rep GameEngine::frame_delay_for_stable_fps = 1000 / fps;//the second part is how many fps we need
std::chrono::high_resolution_clock::time_point GameEngine::begin_time_point = std::chrono::high_resolution_clock::now();//stores the time point before processing game objects and drawing
std::chrono::milliseconds::rep GameEngine::deltaTime;//the time it takes to display the current frame after the previous one, in milliseconds


GameEngine::GameEngine()
{
}

void GameEngine::DisplayEnvironmentInfo()
{
    std::cout << ">>> Begin DisplayEnvironmentInfo <<< " << std::endl;

    SDL_version sdl_version;
    SDL_GetVersion(&sdl_version);
    std::cout << "SDL_GetVersion: " << std::to_string(sdl_version.major) << "." << std::to_string(sdl_version.minor) << "." << std::to_string(sdl_version.patch) << std::endl;

    std::cout << "SDL_GetRevision: " << SDL_GetRevision() << std::endl;

    std::cout << "SDL_GetCurrentVideoDriver: " << SDL_GetCurrentVideoDriver() << std::endl;

    std::cout << "SDL_GetPlatform: " << SDL_GetPlatform() << std::endl;

    std::cout << "SDL_GetDisplayName(0): " << SDL_GetDisplayName(0) << std::endl;

    std::cout << "SDL_GetDisplayName(0): " << SDL_GetDisplayName(0) << std::endl;

    std::cout << ">>> End DisplayEnvironmentInfo <<<" << std::endl;
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
         //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);


        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        //gWindow = SDL_CreateWindow( "Tank Multiplayer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ViewPort::ScreenWidth, ViewPort::ScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        gWindow = SDL_CreateWindow( "Tank Multiplayer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ViewPort::ScreenWidth, ViewPort::ScreenHeight, SDL_WINDOW_SHOWN);

        if( GameEngine::gWindow == nullptr )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            RenderUtils::windowRenderer = SDL_CreateRenderer( GameEngine::gWindow, -1, SDL_RENDERER_ACCELERATED );
            //RenderUtils::windowRenderer = SDL_CreateRenderer( GameEngine::gWindow, -1, SDL_RENDERER_SOFTWARE );
            if(RenderUtils::windowRenderer == nullptr )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(RenderUtils::windowRenderer, 0x00, 0x00, 0x00, 0x00 );
            }
        } //SDL_CreateWindow

    } //Initialize SDL

    //set drawing alpha transparency support (eg. SDL_RenderFillRect)
    SDL_SetRenderDrawBlendMode(RenderUtils::windowRenderer, SDL_BLENDMODE_BLEND);

    #ifndef __EMSCRIPTEN__
    // (STEP 2 / 3)
    //Initialize PNG loading
    int imgFlags = IMG_INIT_JPG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
    }//Initialize PNG loading
    #endif

    // (STEP 3 / 3)
    //Initialize TTF
    if( TTF_Init()  < 0 )
    {
        printf( "TTF could not initialize! Error: %s\n", TTF_GetError());
        success = false;
    } else {
        fpsEntity.fps_component = std::make_unique<FpsComponent>();
        fpsEntity.transform_component->Position.x = 0;
        fpsEntity.transform_component->Position.y = 0;
    }//Initialize TTF

    Running = success;
    return success;
}

//main game loop
void GameEngine::StartGameLoop()
{
    deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(begin_time_point - begin_time_point).count();//stores the duration of procesing the game objects and drawing

#ifdef __EMSCRIPTEN__
    GameEngine::fps = 80;
    GameEngine::begin_time_point = std::chrono::high_resolution_clock::now();//stores the time point before processing game objects and drawing
    GameEngine::deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(begin_time_point - begin_time_point).count();//stores the duration of procesing the game objects and drawing
    // void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
    emscripten_set_main_loop(GameEngine::game_engine_one_iteration, 0, 1);
#else
    game_engine_infinite_loop();
#endif
}

//main game loop
void GameEngine::game_engine_infinite_loop()
{
    //frame cap related valiables
    //80 fps are ok. High fps values might produce incorrect results because of number rounding
     //IMPORTANT! For smooth movement of game objects, the fps value should be choosed based on the update frequency of
    //each object. For example if a tank object moves on the x vector 0.1 pixel / ms then choosing 60 fps will result
    //in a not smooth movement because the object position will be calculated every 16ms. So, the first time its x position
    //will be 16ms* 0.1 = round(1.6) = 2, the next will be 1.6 + 16ms*0.1 = round(1.6 + 1.6)=3 and the next will be 5 etc..
    //For slow moving objects it is better to choose an fps that will move them 1px on each update call.
    //For the above example,80fps will be much better: 12.5*0.1 = round(1.25) = 1, next: 1.25 + 1.25 = round(1.5) = 2, next: 1.5 + 1.25 = round(2.75) = 3, next: 2.75 + 1.25 = round(4) 4 etc...
    GameEngine::fps = 80;
    GameEngine::frame_delay_for_stable_fps = 1000 / fps;//the second part is how many fps we need
    GameEngine::begin_time_point = std::chrono::high_resolution_clock::now();//stores the time point before processing game objects and drawing
    GameEngine::deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(begin_time_point - begin_time_point).count();//stores the duration of procesing the game objects and drawing

    //enter game loop
    while (Running){

        //store the begining time point of the proccesing.
        begin_time_point = std::chrono::high_resolution_clock::now();

        HandleEvents();//process user input from keyboard/mouse/game controlers etc
        Update();//update game objects position, collitions etc
        SDL_RenderClear(RenderUtils::windowRenderer);
        Draw();//draw the objects on screen

        //the duration it took to process the game objects
        deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point).count();

        //std::cout << "gameloop exec time: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - begin_time_point).count() << std::endl;

        //frame cap.
        //If frame finished early wait for the remaining time
       if (deltaTime < frame_delay_for_stable_fps){
           //sleep for the remaining time and set the deltaTime duration again
           std::this_thread::sleep_for(std::chrono::milliseconds(frame_delay_for_stable_fps - deltaTime));
           //std::cout << "sleeping for: " << std::chrono::milliseconds(frame_delay_for_stable_fps - deltaTime).count() << std::endl;
       }
       //End of frame cap


       //display the fps counter if needed
       if (fpsEntity.fps_component->displayFpsCounter){
           deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point).count();
           fpsSystem.Update(deltaTime, fpsEntity.sprite_component, fpsEntity.fps_component);
           renderSystem.RenderInViewport(*fpsEntity.transform_component, *fpsEntity.sprite_component, fpsEntity.viewport_component->viewports[0], game::viewports[fpsEntity.viewport_component->viewports[0].viewportID]);
           //std::cout << "deltatime: " << deltaTime << std::endl;
       }

       //display everything in screen

       SDL_RenderPresent(RenderUtils::windowRenderer);

       deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point).count();
    }
}


void GameEngine::game_engine_infinite_loop2()
{
    GameEngine::fps = 80;
    GameEngine::begin_time_point = std::chrono::high_resolution_clock::now();//stores the time point before processing game objects and drawing
    GameEngine::deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(begin_time_point - begin_time_point).count();//stores the duration of procesing the game objects and drawing

    //enter game loop
    while (Running){
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
       if (fpsEntity.fps_component->displayFpsCounter){
           deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point).count();
           fpsSystem.Update(deltaTime, fpsEntity.sprite_component, fpsEntity.fps_component);
       }
       deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point).count();
        //std::cout << deltaTime << std::endl;

        //store the begining time point of the proccesing.
        begin_time_point = std::chrono::high_resolution_clock::now();

        HandleEvents();//process user input from keyboard/mouse/game controlers etc
        Update();//update game objects position, collitions etc
        SDL_RenderClear(RenderUtils::windowRenderer);
        Draw();//draw the objects on screen

       //display the fps counter if needed
       if (fpsEntity.fps_component->displayFpsCounter){
           //renderSystem.Render(*fpsEntity.transform_component, *fpsEntity.sprite_component, game::viewports);
           renderSystem.RenderInViewport(*fpsEntity.transform_component, *fpsEntity.sprite_component, fpsEntity.viewport_component->viewports[0], game::viewports[fpsEntity.viewport_component->viewports[0].viewportID]);
       }

       //display everything in screen
       SDL_RenderPresent(RenderUtils::windowRenderer);
    }
}



void GameEngine::game_engine_one_iteration()
{
    //store the begining time point of the proccesing.
    begin_time_point = std::chrono::high_resolution_clock::now();

    HandleEvents();//process user input from keyboard/mouse/game controlers etc
    Update();//update game objects position, collitions etc
    SDL_RenderClear(RenderUtils::windowRenderer);
    Draw();//draw the objects on screen

    //SDL_Delay(12);

    //the duration it took to process the game objects
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
    if (fpsEntity.fps_component->displayFpsCounter){
        deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point).count();
        fpsSystem.Update(deltaTime, fpsEntity.sprite_component, fpsEntity.fps_component);
        //renderSystem.Render(*fpsEntity.transform_component, *fpsEntity.sprite_component, game::viewports);
        renderSystem.RenderInViewport(*fpsEntity.transform_component, *fpsEntity.sprite_component, fpsEntity.viewport_component->viewports[0], game::viewports[fpsEntity.viewport_component->viewports[0].viewportID]);
    }


    //display everything in screen
    SDL_RenderPresent(RenderUtils::windowRenderer);

    deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point).count();
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

        for (const auto& entity : game::entityObjects){
            if(entity->tank_input_component){
                tankInputSystem.handleEvent(e, *entity);
            }
            if (entity->zoom_input_component){
                ZoomInputSystem::handleEvent(e, *entity);
            }
        }

        //A player might press the fire key and a new bullet game object
        //has to be created. It is placed in the gameObjects_for_addition vector
        //so that after returning fron the previous handleEvent call, it will be added to the
        //gameObjects vector.
        if (!game::entityObjects_for_addition.empty()){
            std::move(game::entityObjects_for_addition.begin(), game::entityObjects_for_addition.end(), std::back_inserter(game::entityObjects));  // ##
            game::entityObjects_for_addition.clear();
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
    for(auto it = game::entityObjects.begin(); it != game::entityObjects.end();)
    {
        //update game object
        //Because after calling update on each object, the object might non need to exist any more
        //it might mark itself for deletion (Exists=False), so we should remove it from the vector.
        //To remove an item from the vector while iterating it, we should follow this method,
        //using an iterator.
        if((*it)->rigid_body2d_component){
            physicsSystem.Update(deltaTime,
                                  *(*it)->transform_component,
                                  *(*it)->rigid_body2d_component);

            //game::viewports[0].FollowEntity(*(*it)->transform_component, *(*it)->sprite_component, GameEngine::sceneManager.levelWidth, GameEngine::sceneManager.levelHeight);
            if ((*it)->viewport_component->movesTheCamera){
                for (auto& viewportTarget : (*it)->viewport_component->viewports){
                    if (viewportTarget.movesTheCamera){
                        ViewPort::FollowEntity(
                                    *(*it)->transform_component,
                                    *(*it)->sprite_component,
                                    viewportTarget,
                                    game::viewports[viewportTarget.viewportID],
                                    ViewPort::levelWidth,
                                    ViewPort::levelHeight);
                    }
                }
            }
        } //if((*it)->rigid_body2d_component

        if((*it)->zoom_input_component){
            ZoomInputSystem::Update(deltaTime, *(*it));
        }

        ++it;
    }
}

//draws the game objects
void GameEngine::Draw()
{
    //all entities can have zero or more viewport targets.
    //Loop through all game viewports and if an entity wants to be rendered
    //in a viewport with the same viewPortIndex then render it
    for (size_t viewPortIndex = 0; viewPortIndex < game::viewports.size(); viewPortIndex++){

        //render viewport background if exists
        if (game::viewports[viewPortIndex].background_sprite_component) {
            renderSystem.RenderViewportSprite(*game::viewports[viewPortIndex].background_sprite_component,
                                              game::viewports[viewPortIndex]);
        }

        //render entities inside the viewport
        for (const auto& entity : game::entityObjects){
            if (entity->viewport_component){
                //if an entity has a viewport component then loop through all
                //viewport targets it contains if one maches the current viewPortIndex
                for (auto& viewportTarget : entity->viewport_component->viewports){
                    if (viewportTarget.viewportID == viewPortIndex){
                        renderSystem.RenderInViewport(*entity->transform_component,
                                                      *entity->sprite_component,
                                                      viewportTarget,
                                                      game::viewports[viewPortIndex]);
                        break;
                    }
                } // for (auto& viewport ... entity viewport targets loop
            }
        }//for (const auto& entity ... entities loop

    }//for (size_t ... viewports loop
}//Draw
