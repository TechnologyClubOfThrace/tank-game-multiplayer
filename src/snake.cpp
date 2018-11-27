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
#include "game_objects.h"


Snake::Snake() : RotationAngle(0.26)
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
        case SDLK_w: RotationAngle.AddAngleDirection(AngleDirection::Up);break;
        case SDLK_s: RotationAngle.AddAngleDirection(AngleDirection::Down);break;
        case SDLK_d: RotationAngle.AddAngleDirection(AngleDirection::Right);break;
        case SDLK_a: RotationAngle.AddAngleDirection(AngleDirection::Left);break;

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
        case SDLK_s: RotationAngle.RemoveAngleDirection(AngleDirection::Down);break;
        case SDLK_w: RotationAngle.RemoveAngleDirection(AngleDirection::Up);break;
        case SDLK_a: RotationAngle.RemoveAngleDirection(AngleDirection::Left);break;
        case SDLK_d: RotationAngle.RemoveAngleDirection(AngleDirection::Right);break;

        case SDLK_p: Velocity.x /= FastTankSpeedMultiplier; Velocity.y /= FastTankSpeedMultiplier;break;
        }
    }
}

void Snake::Update(std::chrono::milliseconds::rep deltaTime)
{
    //std::cout << "deltatime: " << deltaTime << std::endl;

    RotationAngle.Apply(this->Velocity, deltaTime);

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
}

void Snake::setCamera( SDL_Rect& camera )
{
    /*
    //Center the camera over the dot
    camera.x = ( mBox.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( mBox.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds
    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
    */
}

void Snake::FireBullet()
{
    auto bullet = std::make_unique<Bullet>();
    bullet->Texture.WindowRenderer = this->snakeTexture.WindowRenderer;
    bullet->Texture.loadFromFile("bullet_w65h20.png");

    double canon_x = static_cast<int>(std::round(Position.x + DOT_WIDTH/2 + DOT_WIDTH/2*cos(RotationAngle.CurrentAngle * M_PI / 180.0)));
    double canon_y = static_cast<int>(std::round(Position.y + DOT_HEIGHT/2 + DOT_WIDTH/2*sin(RotationAngle.CurrentAngle * M_PI / 180.0)));

    //bullet->Position.x = Position.x + 55 + 71*cos(RotationAngle.CurrentAngle * M_PI / 180.0);
    //bullet->Position.y = Position.y  + 14 + 71*sin(RotationAngle.CurrentAngle * M_PI / 180.0);
    bullet->Position.x = canon_x;
    bullet->Position.y = canon_y;

    //bullet->Position = this->Position;
    //bullet->Position.Rotate(this->RotationAngle.CurrentAngle * M_PI / 180.0);
    //bullet->Position.Rotate(0.01);
    bullet->Velocity.x = TankDirection == AngleDirection::Forward || TankDirection == AngleDirection::None ? this->Velocity.x * 5 : -this->Velocity.x * 5;
    bullet->Velocity.y = TankDirection == AngleDirection::Forward || TankDirection == AngleDirection::None ? this->Velocity.y * 5 : -this->Velocity.y * 5;
    bullet->RotationAngle = this->RotationAngle;
    bullet->level = this->level;
    GameObjects::gameObjects_for_addition.emplace_back(std::move(bullet));
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

void Snake::Draw( SDL_Rect& camera )
{
    //Show the tank
    //gDotTexture.render( mBox.x - camera.x, mBox.y - camera.y );

    snakeTexture.render(static_cast<int>(std::round(Position.x)),
                        static_cast<int>(std::round(Position.y)),
                        nullptr,RotationAngle.CurrentAngle);




    SDL_Rect rect;
    //rect.x = static_cast<int>(std::round(Position.x));
    //rect.y = static_cast<int>(std::round(Position.y));
    rect.w = 100;
    rect.h = 20;
    Vector2D v;
    //v.x = 32;
    //v.y = 32;
    //v.Rotate(RotationAngle.CurrentAngle);
    //v.Rotate(RotationAngle.CurrentAngle);


    //rect.x = Position.x + 120*cosf(RotationAngle.CurrentAngle)  ;
    //rect.y = Position.y + 120*sinf(RotationAngle.CurrentAngle) ;

    //rect.x = static_cast<int>(std::round(Position.x + 60 + 71*cos(RotationAngle.CurrentAngle * M_PI / 180.0)));
    //rect.y = static_cast<int>(std::round(Position.y + 20 + 71*sin(RotationAngle.CurrentAngle * M_PI / 180.0)));


    //std::cout << "rotation angle: " << RotationAngle.CurrentAngle << std::endl;

    //double xt = (rect.x * cos(std::div(RotationAngle.CurrentAngle,180).rem)) - (rect.y * sin(std::div(RotationAngle.CurrentAngle,180).rem));
    // yt = (rect.y * cos(std::div(RotationAngle.CurrentAngle, 180).rem)) + (rect.x * sin(std::div(RotationAngle.CurrentAngle,180).rem));
    //rect.x = static_cast<int>(std::round(xt));
    //rect.y = static_cast<int>(std::round(yt));

    //rect.x = static_cast<int>(std::round(Position.x + DOT_WIDTH/2 + DOT_WIDTH/2*cos(RotationAngle.CurrentAngle * M_PI / 180.0)));
    //rect.y = static_cast<int>(std::round(Position.y + DOT_HEIGHT/2 + DOT_WIDTH/2*sin(RotationAngle.CurrentAngle * M_PI / 180.0)));

    //SDL_SetRenderDrawColor(snakeTexture.WindowRenderer, 255, 10, 255, 255);
    //SDL_RenderFillRect(snakeTexture.WindowRenderer, &rect);

}
