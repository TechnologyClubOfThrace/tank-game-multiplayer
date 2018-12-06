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
#include "tank.h"
#include "bullet.h"
#include "game.h"


Tank::Tank() : RotationVector(0.26 * M_PI / 180.0)
{
    //Initialize the collision box
    Position.x = 50;
    Position.y = 50;

    Velocity.x = 0.00;
    Velocity.y = 0.00;
    previousVelocity = Velocity;
}

void Tank::handleEvent( SDL_Event& e )
{
    switch (state) {
    case enumState::stopped:
        switch( e.key.keysym.sym )
        {
        case SDLK_w:case SDLK_s:case SDLK_a:case SDLK_d:
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
            setAngleDirection(e.key.keysym);
            state = enumState::moveForward;
            Velocity.x = NormalTankSpeed;
            break;
        }
        }
        break;//stopped

    case enumState::moveForward:
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
        {
        setAngleDirection(e.key.keysym);
        switch( e.key.keysym.sym )
        {
        case SDLK_q: Velocity.x = -Velocity.x; Velocity.y = -Velocity.y; state = enumState::moveBackwards; break;
        case SDLK_z: previousVelocity = Velocity; Velocity.x = 0; Velocity.y = 0; state = enumState::stoppedFromForwards; break;
        case SDLK_m: Velocity.x *= this->FastTankSpeedMultiplier; Velocity.y *= this->FastTankSpeedMultiplier;break;
        case SDLK_SPACE: FireBullet();break;
        }
        }
        break;

    case enumState::moveBackwards:
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
        {
        setAngleDirection(e.key.keysym);
        switch( e.key.keysym.sym )
        {
        case SDLK_q: Velocity.x = -Velocity.x; Velocity.y = -Velocity.y; state = enumState::moveForward; break;
        case SDLK_z: previousVelocity = Velocity; Velocity.x = 0; Velocity.y = 0; state = enumState::stoppedFromBackwards; break;
        case SDLK_m: Velocity.x *= this->FastTankSpeedMultiplier; Velocity.y *= this->FastTankSpeedMultiplier;break;
        case SDLK_SPACE: FireBullet();break;
        }
        }
        break;

    case enumState::stoppedFromForwards:
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
        {
        setAngleDirection(e.key.keysym);
        switch( e.key.keysym.sym )
        {
        case SDLK_z: case SDLK_q: Velocity = previousVelocity; state = enumState::moveForward; break;
        case SDLK_SPACE: FireBullet();break;
        }
        }
        break;


    case enumState::stoppedFromBackwards:
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
        {
        setAngleDirection(e.key.keysym);
        switch( e.key.keysym.sym )
        {
        case SDLK_z: case SDLK_q: Velocity = previousVelocity; state = enumState::moveBackwards; break;
        case SDLK_SPACE: FireBullet();break;
        }
        }
        break;
    } // switch state

    //If a key was released
    if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_s: RotationVector.RemoveAngleDirection(AngleDirection::Down);break;
        case SDLK_w: RotationVector.RemoveAngleDirection(AngleDirection::Up);break;
        case SDLK_a: RotationVector.RemoveAngleDirection(AngleDirection::Left);break;
        case SDLK_d: RotationVector.RemoveAngleDirection(AngleDirection::Right);break;
        case SDLK_m: Velocity.x /= FastTankSpeedMultiplier; Velocity.y /= FastTankSpeedMultiplier;break;
        }
    }
}

void Tank::setAngleDirection(SDL_Keysym &keysym)
{
    switch (keysym.sym) {
    case SDLK_w: RotationVector.AddAngleDirection(AngleDirection::Up);break;
    case SDLK_s: RotationVector.AddAngleDirection(AngleDirection::Down);break;
    case SDLK_d: RotationVector.AddAngleDirection(AngleDirection::Right);break;
    case SDLK_a: RotationVector.AddAngleDirection(AngleDirection::Left);break;
    }
}

void Tank::Update(std::chrono::milliseconds::rep deltaTime)
{
    //std::cout << "deltatime: " << deltaTime << std::endl;

    state == enumState::moveForward ||
    state == enumState::moveBackwards ?
                RotationVector.Apply(this->Velocity, deltaTime) :
                RotationVector.Apply(this->previousVelocity, deltaTime);

    //position equation
    //P(t)=P(0)+v*t

    if (TankDirection != AngleDirection::None){
        //Move the tank based on the user input
        //check if the user stoped the tank (AngleDirection::None)
        Position.x += Velocity.x * deltaTime;

        //If the dot went too far to the left or right or touched a wall
        if( ( Position.x < 0 ) || ( Position.x + texture.getWidth() > level->tileMap.level_width) || touchesWall(level) )
        {
            //move back
            Position.x -= Velocity.x * deltaTime;
        }

        //Move the dot up or down
        Position.y += Velocity.y * deltaTime ;

        //If the dot went too far up or down or touched a wall
        if( ( Position.y < 0 ) || ( Position.y + texture.getHeight() > level->tileMap.level_height) || touchesWall(level) )
        {
            //move back
            Position.y -= Velocity.y * deltaTime;
        }
    }

    game::viewports[0].camera.followGameObject(*this, level->tileMap.level_width, level->tileMap.level_height);
}


void Tank::FireBullet()
{
    auto bullet = std::make_unique<Bullet>();
    bullet->texture.WindowRenderer = this->texture.WindowRenderer;
    bullet->texture.loadFromFile("bullet_w65h20.png");

    bullet->Position.x = Position.x + 55 + 71*cos(RotationVector.CurrentAngleDegrees * M_PI / 180);//todo
    bullet->Position.y = Position.y  + 14 + 71*sin(RotationVector.CurrentAngleDegrees * M_PI / 180);

    switch (state) {
    case enumState::moveForward:
        bullet->Velocity.x = this->Velocity.x * 5;
        bullet->Velocity.y = this->Velocity.y * 5;
        break;
    case enumState::moveBackwards:
        bullet->Velocity.x = -this->Velocity.x * 5;
        bullet->Velocity.y = -this->Velocity.y * 5;
        break;
    case enumState::stoppedFromForwards:
        bullet->Velocity.x = this->previousVelocity.x * 5;
        bullet->Velocity.y = this->previousVelocity.y * 5;
        break;
    case enumState::stoppedFromBackwards:
        bullet->Velocity.x = -this->previousVelocity.x * 5;
        bullet->Velocity.y = -this->previousVelocity.y * 5;
        break;
    case enumState::stopped:
        break;//the tank cannot fire when game begins
    }

    bullet->RotationAngle = this->RotationVector;
    bullet->level = this->level;
    game::gameObjects_for_addition.emplace_back(std::move(bullet));
}

bool Tank::touchesWall(Level* level)
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
            box.w = texture.getWidth();
            box.h = texture.getHeight();

            if (SDL_HasIntersection(&box, &bb))
                return true;
        }
    }

    //If no wall tiles were touched
    return false;
}


void Tank::Draw()
{
    //Show the tank
    texture.render(static_cast<int>(std::round(Position.x - game::viewports[0].camera.frame.x)),
                   static_cast<int>(std::round(Position.y - game::viewports[0].camera.frame.y)),
                   nullptr, RotationVector.CurrentAngleDegrees);
}

void Tank::Draw(size_t viewportIndex)
{
    if (viewportIndex == 1 || viewportIndex == 2) {

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

        if (viewportIndex == 2){
            SDL_SetRenderDrawColor(texture.WindowRenderer, 0, 0, 0, 80);
            SDL_RenderFillRect(texture.WindowRenderer,
                         &game::viewports[viewportIndex].frame);
        }
        SDL_RenderCopyEx(texture.WindowRenderer,
                          texture.mTexture,
                          &source_rect,
                          &dest_rect,
                          RotationVector.CurrentAngleDegrees,
                          nullptr,SDL_FLIP_NONE);
    }
}
