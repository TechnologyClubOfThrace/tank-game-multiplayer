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

#include <cmath>
#include <iostream>
#include <math.h>
#include <memory>
#include "snake.h"
#include "bullet.h"
#include "game.h"


Snake::Snake() : RotationVector(0.26 * M_PI / 180.0)
{
    //Initialize the collision box
    Position.x = 50;
    Position.y = 50;

    Velocity.x = NormalTankSpeed;
    Velocity.y = 0.00;
}

void Snake::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_w: RotationVector.AddAngleDirection(AngleDirection::Up);break;
        case SDLK_s: RotationVector.AddAngleDirection(AngleDirection::Down);break;
        case SDLK_d: RotationVector.AddAngleDirection(AngleDirection::Right);break;
        case SDLK_a: RotationVector.AddAngleDirection(AngleDirection::Left);break;

        case SDLK_SPACE: FireBullet();break;  //fire

        case SDLK_o://go forward
            if (TankDirection == AngleDirection::Backward || TankDirectionBeforeStopping == AngleDirection::Backward){
                Velocity.x = -Velocity.x; Velocity.y = -Velocity.y;
            }
            TankDirection = AngleDirection::Forward;
            TankDirectionBeforeStopping = TankDirection;
            break; //forward

        case SDLK_k: //go backwards
            if (TankDirection == AngleDirection::Forward || TankDirectionBeforeStopping == AngleDirection::Forward){
                Velocity.x = -Velocity.x; Velocity.y = -Velocity.y;
            }
            TankDirection = AngleDirection::Backward;
            TankDirectionBeforeStopping = TankDirection;
            break; //forward

        case SDLK_m: //stop tank
           //RotationAngle.angle_directions.clear();
            if (TankDirection != AngleDirection::None){
               TankDirectionBeforeStopping = TankDirection;
               TankDirection = AngleDirection::None;
            } else {
                //tank was allready stopped, so move again in the last direction before stopped
                TankDirection = TankDirectionBeforeStopping;
            }
           break;


        case SDLK_p: Velocity.x *= FastTankSpeedMultiplier; Velocity.y *= FastTankSpeedMultiplier; break;

        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_s: RotationVector.RemoveAngleDirection(AngleDirection::Down);break;
        case SDLK_w: RotationVector.RemoveAngleDirection(AngleDirection::Up);break;
        case SDLK_a: RotationVector.RemoveAngleDirection(AngleDirection::Left);break;
        case SDLK_d: RotationVector.RemoveAngleDirection(AngleDirection::Right);break;

        case SDLK_p: Velocity.x /= FastTankSpeedMultiplier; Velocity.y /= FastTankSpeedMultiplier;break;
        }
    }
}

void Snake::Update(std::chrono::milliseconds::rep deltaTime)
{
    //std::cout << "deltatime: " << deltaTime << std::endl;

    RotationVector.Apply(this->Velocity, deltaTime);

    //position equation
    //P(t)=P(0)+v*t

    if (TankDirection != AngleDirection::None){
        //Move the tank based on the user input
        //check if the user stoped the tank (AngleDirection::None)
        Position.x += Velocity.x * deltaTime;

        //If the dot went too far to the left or right or touched a wall
        if( ( Position.x < 0 ) || ( Position.x + DOT_WIDTH > level->tileMap.level_width) || touchesWall(level) )
        {
            //move back
            Position.x -= Velocity.x * deltaTime;
        }

        //Move the dot up or down
        Position.y += Velocity.y * deltaTime ;

        //If the dot went too far up or down or touched a wall
        if( ( Position.y < 0 ) || ( Position.y + DOT_HEIGHT > level->tileMap.level_height) || touchesWall(level) )
        {
            //move back
            Position.y -= Velocity.y * deltaTime;
        }
    }

    game::viewports[0].camera.followGameObject(*this, level->tileMap.level_width, level->tileMap.level_height);
}


void Snake::FireBullet()
{
    auto bullet = std::make_unique<Bullet>();
    bullet->texture.WindowRenderer = this->texture.WindowRenderer;
    bullet->texture.loadFromFile("bullet_w65h20.png");

    double canon_x = static_cast<int>(std::round(Position.x - game::viewports[0].camera.frame.x + DOT_WIDTH/2 + DOT_WIDTH/2*cos(RotationVector.CurrentAngleDegrees * M_PI / 180)));
    double canon_y = static_cast<int>(std::round(Position.y - game::viewports[0].camera.frame.y + DOT_HEIGHT/2 + DOT_WIDTH/2*sin(RotationVector.CurrentAngleDegrees * M_PI / 180)));

    bullet->Position.x = Position.x + 55 + 71*cos(RotationVector.CurrentAngleDegrees * M_PI / 180);//todo
    bullet->Position.y = Position.y  + 14 + 71*sin(RotationVector.CurrentAngleDegrees * M_PI / 180);
    //bullet->Position.x = canon_x;
    //bullet->Position.y = canon_y;

    //bullet->Position = this->Position;
    //bullet->Position.Rotate(this->RotationAngle.CurrentAngle * M_PI / 180.0);
    //bullet->Position.Rotate(0.01);
    bullet->Velocity.x = TankDirection == AngleDirection::Forward || TankDirection == AngleDirection::None ? this->Velocity.x * 1.1 : -this->Velocity.x * 1.1;
    bullet->Velocity.y = TankDirection == AngleDirection::Forward || TankDirection == AngleDirection::None ? this->Velocity.y * 1.1 : -this->Velocity.y * 1.1;
    bullet->RotationAngle = this->RotationVector;
    bullet->level = this->level;
    game::gameObjects_for_addition.emplace_back(std::move(bullet));
}

bool Snake::touchesWall(Level* level)
{
    //Go through the tiles
    for(size_t i = 0; i < level->Tiles.size(); ++i )
    {
        //If the tile is a wall type tile
        if( !(level->Tiles[i].sprite.index == 4))
        {
            auto bb = level->Tiles[i].getBox();
            SDL_Rect box;
            box.x = static_cast<int>(std::round(Position.x));
            box.y = static_cast<int>(std::round(Position.y));
            box.w = DOT_WIDTH;
            box.h = DOT_HEIGHT;

            if (SDL_HasIntersection(&box, &bb))
                return true;
        }
    }

    //If no wall tiles were touched
    return false;
}

void Snake::Draw()
{
    //Show the tank
    texture.render(static_cast<int>(std::round(Position.x - game::viewports[0].camera.frame.x)),
                        static_cast<int>(std::round(Position.y - game::viewports[0].camera.frame.y)),
                        nullptr,RotationVector.CurrentAngleDegrees);

    /*
    SDL_Rect rect;
    rect.w = 20;
    rect.h = 20;
    rect.x = static_cast<int>(std::round(Position.x - game::viewports[0].camera.frame.x + DOT_WIDTH/2 + DOT_WIDTH/2*cos(RotationAngle.CurrentAngle * M_PI / 180.0)));
    rect.y = static_cast<int>(std::round(Position.y - game::viewports[0].camera.frame.y + DOT_HEIGHT/2 + DOT_WIDTH/2*sin(RotationAngle.CurrentAngle * M_PI / 180.0)));
    SDL_SetRenderDrawColor(texture.WindowRenderer, 255, 10, 255, 255);
    SDL_RenderFillRect(texture.WindowRenderer, &rect);
    */
}

void Snake::Draw(size_t viewportIndex)
{
    if (viewportIndex != 1) return;

    SDL_Rect source_rect;
    source_rect.x = 0;
    source_rect.y = 0;
    source_rect.w = static_cast<int>(round(texture.getWidth()));
    source_rect.h = static_cast<int>(round(texture.getHeight()));

    SDL_Rect dest_rect;
    dest_rect.x = static_cast<int>(round(game::viewports[viewportIndex].frame.x + Position.x/10));
    dest_rect.y = static_cast<int>(round(game::viewports[viewportIndex].frame.y + Position.y/10));
    dest_rect.w = static_cast<int>(round(texture.getWidth()/10));
    dest_rect.h = static_cast<int>(round(texture.getHeight()/10));

    SDL_RenderCopyEx(texture.WindowRenderer,
                      texture.mTexture,
                      &source_rect,
                      &dest_rect,
                      RotationVector.CurrentAngleDegrees,
                      nullptr,SDL_FLIP_NONE);
}
