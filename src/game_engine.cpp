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

// ======= FRAME CAPPING RELATED =======
int GameEngine::fps = 67;
std::chrono::nanoseconds::rep GameEngine::frame_delay_for_stable_fps = 1000 / fps;//the second part is how many fps we need
std::chrono::high_resolution_clock::time_point GameEngine::begin_time_point = std::chrono::high_resolution_clock::now();//stores the time point before processing game objects and drawing
double GameEngine::deltaTime = 0; //the time it takes to display the current frame after the previous one, in milliseconds

int GameEngine::max_fps_ticks = 20;
int GameEngine::fps_ticks = 0;

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

        //display SDL version
        SDL_version compiled;
        SDL_version linked;
        SDL_VERSION(&compiled);
        SDL_GetVersion(&linked);
        std::cout << "We compiled against SDL version: " <<
               compiled.major << "." << compiled.minor << "." << compiled.patch << std::endl;
        std::cout << "But we are linking against SDL version: " <<
               linked.major  << "." << linked.minor << "." << linked.patch << std::endl;


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
            RenderUtils::windowRenderer = SDL_CreateRenderer( GameEngine::gWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE );
            //RenderUtils::windowRenderer = SDL_CreateRenderer( GameEngine::gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE );
            //RenderUtils::windowRenderer = SDL_CreateRenderer( GameEngine::gWindow, -1, SDL_RENDERER_SOFTWARE);
            if(RenderUtils::windowRenderer == nullptr )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(RenderUtils::windowRenderer, 0x00, 0x00, 0x00, 0x00 );
                DisplayRenderInfo();
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

void GameEngine::DisplayRenderInfo()
{
    SDL_RendererInfo render_info;
    SDL_GetRendererInfo(RenderUtils::windowRenderer, &render_info);
    std::cout << " Renderer name: " << render_info.name << std::endl;
    std::cout << " Renderer max_texture_width: " << render_info.max_texture_width << std::endl;
    std::cout << " Renderer max_texture_height: " << render_info.max_texture_height << std::endl;
}

//main game loop
void GameEngine::StartGameLoop()
{
    GameEngine::deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(begin_time_point - begin_time_point).count();//stores the duration of procesing the game objects and drawing
#ifdef __EMSCRIPTEN__
    std::cout << "sizeof(long double): " << sizeof(long double) << std::endl;
    std::cout << "sizeof(double): " << sizeof(double) << std::endl;
    GameEngine::fps = 80;
    GameEngine::begin_time_point = std::chrono::high_resolution_clock::now();//stores the time point before processing game objects and drawing
    GameEngine::deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(begin_time_point - begin_time_point).count();//stores the duration of procesing the game objects and drawing
    // void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
    emscripten_set_main_loop(GameEngine::game_engine_one_iteration, 0, 1);
#else
    game_engine_infinite_loop_simple_vsync();
#endif
}

//main game loop
void GameEngine::game_engine_infinite_loop_simple_vsync()
{
    auto begin_time_point_steady = std::chrono::steady_clock::now();//stores the time point before processing game objects and drawing
    long long ll_delta_time = 1;

    //enter game loop
    while (Running){
       //store the begining time point of the proccesing.
       begin_time_point_steady = std::chrono::steady_clock::now(); //stores the time point before processing game objects and drawing
       GameEngine::deltaTime = ll_delta_time / 1000000.00;
       //std::cout << "game_engine_infinite_loop_simple_vsync deltaTime: " << GameEngine::deltaTime << std::endl;

        HandleEvents();//process user input from keyboard/mouse/game controlers etc
        Update();//update game objects position, collitions etc
        SDL_RenderClear(RenderUtils::windowRenderer);
        Draw();//draw the objects on screen


       //display the fps counter if needed

       if (fpsEntity.fps_component->displayFpsCounter){
           FpsSystem::Update(ceil(GameEngine::deltaTime), fpsEntity);
           fpsEntity.fps_component->entities_count = game::entityObjects.size();
           RenderSystem::RenderInViewport(*fpsEntity.transform_component, *fpsEntity.sprite_component, fpsEntity.target_viewport_component->target_viewports[0], game::viewports[fpsEntity.target_viewport_component->target_viewports[0].viewportID]);
       }


       //display everything in screen
       SDL_RenderPresent(RenderUtils::windowRenderer);

       ll_delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - begin_time_point_steady).count();
    }
}

//game loop for emscripten
void GameEngine::game_engine_one_iteration()
{
   static auto begin_time_point_steady_ems = std::chrono::steady_clock::now();//stores the time point before processing game objects and drawing
   static long long ll_delta_time_ems = 1;

   //store the begining time point of the proccesing.
   begin_time_point_steady_ems = std::chrono::steady_clock::now(); //stores the time point before processing game objects and drawing
   GameEngine::deltaTime = ll_delta_time_ems / static_cast<double>(1000000.00);
   std::cout << "game_engine_one_iteration deltaTime: " << GameEngine::deltaTime << std::endl;

    HandleEvents();//process user input from keyboard/mouse/game controlers etc
    Update();//update game objects position, collitions etc
    SDL_RenderClear(RenderUtils::windowRenderer);
    Draw();//draw the objects on screen


   //display the fps counter if needed

   if (fpsEntity.fps_component->displayFpsCounter){
       FpsSystem::Update(ceil(GameEngine::deltaTime), fpsEntity);
       fpsEntity.fps_component->entities_count = game::entityObjects.size();
       RenderSystem::RenderInViewport(*fpsEntity.transform_component, *fpsEntity.sprite_component, fpsEntity.target_viewport_component->target_viewports[0], game::viewports[fpsEntity.target_viewport_component->target_viewports[0].viewportID]);
   }


   //display everything in screen
   SDL_RenderPresent(RenderUtils::windowRenderer);

   //std::this_thread::sleep_for(std::chrono::milliseconds(5));

   ll_delta_time_ems = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - begin_time_point_steady_ems).count();
}


/*
void GameEngine::game_engine_one_iteration()
{
    //store the begining time point of the proccesing.
    begin_time_point = std::chrono::high_resolution_clock::now();

    HandleEvents();//process user input from keyboard/mouse/game controlers etc
    Update();//update game objects position, collitions etc
    SDL_RenderClear(RenderUtils::windowRenderer);
    Draw();//draw the objects on screen

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
       fps_ticks++;
       if (fps_ticks > max_fps_ticks){
           fps_ticks = 0;
           deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point).count();
           fpsEntity.fps_component->entities_count = game::entityObjects.size();
           FpsSystem::Update(deltaTime, fpsEntity);
           //std::cout << "deltatime: " << deltaTime << std::endl;
       }
       RenderSystem::RenderInViewport(*fpsEntity.transform_component, *fpsEntity.sprite_component, fpsEntity.target_viewport_component->target_viewports[0], game::viewports[fpsEntity.target_viewport_component->target_viewports[0].viewportID]);
   }


    //display everything in screen
    SDL_RenderPresent(RenderUtils::windowRenderer);

    deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - begin_time_point).count();
}
*/


//Smooth movement
//Sluttering, delta time, frame limit, SDL_GetPerformanceCounter, SDL_GetPerformanceFrequency
//capping frame rate, accumulator
void GameEngine::HandleEvents()
{
    //loop for eny pending events
    while(SDL_PollEvent(&e) != 0 )
    {
        //User requests quit
        if(e.type == SDL_QUIT)
        {
             Running = false;
        }

        for (const auto& entity : game::entityObjects){
            //ZoomInputSystem
            if (entity->zoom_input_component){
                ZoomInputSystem::HandleEvent(e, *entity);
            }//ZoomInputSystem

            //tankInputSystem
            if(entity->tank_input_component){
                TankInputSystem::HandleEvent(e, *entity);
            }//tankInputSystem
        }

        //A player might press the fire key and a new bullet game object
        //has to be created. It is placed in the gameObjects_for_addition vector
        //so that after returning fron the previous handleEvent call, it will be added to the
        //gameObjects vector.
        if (!game::entityObjects_for_addition.empty()){
            std::move(game::entityObjects_for_addition.begin(), game::entityObjects_for_addition.end(), std::back_inserter(game::entityObjects));
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
    for(std::vector<std::unique_ptr<Entity>>::const_iterator it = game::entityObjects.begin(); it != game::entityObjects.end();)
    {
        //ZoomInputSystem >>> zoom_input_component
        //IMPORTANT! zoom handling should be before the FollowEntity else
        //zooming is not smooth.
        if((*it)->zoom_input_component){
            ZoomInputSystem::Update(GameEngine::deltaTime, *(*it));
        }//ZoomInputSystem >>> zoom_input_component

        //physicsSystem >>> rigid_body2d_component
        if((*it)->rigid_body2d_component){
            PhysicsSystem::Update(GameEngine::deltaTime, *(*it), it);
            //PhysicsSystem::Update_test(deltaTime, *(*it), it);
        }//physicsSystem >>> rigid_body2d_component

        //FollowEntity
        if ((*it)->target_viewport_component){
            if ((*it)->target_viewport_component->cameraFollowerViewPortTargetIndex != std::numeric_limits<size_t>::max()){
                        ViewPort::FollowEntity(
                                    *(*it)->transform_component,
                                    *(*it)->sprite_component,
                                    game::viewports[(*it)->target_viewport_component->cameraFollowerViewPortTargetIndex]);

            }
        }//FollowEntity

        //check if the entity is marked for removal
        if (!(*it)->properties_component->shouldBeRemoved){
            ++it;
        } else {
            it = game::entityObjects.erase(it);
        }

    } //for(auto it = game::entityObjects.begin();....
} //void GameEngine::Update()

//draws the game objects
void GameEngine::Draw()
{
    //all entities can have zero or more viewport targets.
    //Loop through all game viewports and if an entity wants to be rendered
    //in a viewport with the same viewPortIndex then render it
    for (size_t viewPortIndex = 0; viewPortIndex < game::viewports.size(); viewPortIndex++){

        //render viewport background if exists
        if (game::viewports[viewPortIndex].background_sprite_component) {
            RenderSystem::RenderViewportSprite(*game::viewports[viewPortIndex].background_sprite_component,
                                              game::viewports[viewPortIndex]);
        }

        //render entities inside the viewport
        for (const auto& entity : game::entityObjects){
            if (entity->target_viewport_component){
                //if an entity has a viewport component then loop through all
                //viewport targets it contains if one maches the current viewPortIndex
                for (const auto& viewportTarget : entity->target_viewport_component->target_viewports){
                    if (viewportTarget.viewportID == viewPortIndex){
                        RenderSystem::RenderInViewport(*entity->transform_component,
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
