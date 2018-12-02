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

#include "vector2d_angle.h"
#include <iostream>
#include <algorithm>

Vector2DAngle::Vector2DAngle(double angleRadiansPerMilliSec) : AngleRadiansPerMilliSec(angleRadiansPerMilliSec)
{
    mCurrentAngleDirection = AngleDirection::None;
}

void Vector2DAngle::AddAngleDirection(AngleDirection angleDirection)
{
    this->mCurrentAngleDirection = angleDirection;
    angle_directions.emplace_back(angleDirection);
}

void Vector2DAngle::RemoveAngleDirection(AngleDirection angleDirection)
{
    if (angle_directions.size() == 1){
        //remove the direction and clear the vector.
        mCurrentAngleDirection = AngleDirection::None;
        angle_directions.clear();
    } else {
        //more than on direction keys were down.
        //delete the angleDirection and set the last angleDirection of the vector as active
        angle_directions.erase(std::remove(angle_directions.begin(), angle_directions.end(), static_cast<AngleDirection>(angleDirection)));
        this->mCurrentAngleDirection = angle_directions.back();
    }
}

//Sets the tank angle based on the user input
//It rotates the velocity angle so that the tank changes direction
//and sets the CurrentAngle variable to the new angle, so that the tank is rendered
//in parallel (rotated) with the velocity vector.
//
//Also there are some restrictions in place:
//If the tank is moving to the right (velocity vector y is almost zero and x a possitive number, and the user
//press the left direction button, it is ignored. The same for the other directions
//
//There is also an ignoreValue for movement correction. For example the tank with a velocity vector x=0.0001, y=0.01
//is considered to going straight down
void Vector2DAngle::Apply(Vector2D &velocity_vector, std::chrono::milliseconds::rep deltaTime)
{
    if (mCurrentAngleDirection != AngleDirection::None){

        //std::cout << velocity_vector.x << " y:" << velocity_vector.y << std::endl;

        //std::cout << "AnglePerMilliSec * deltaTime: " << (AnglePerMilliSec * deltaTime) << std::endl;
        const double angleStepRadians = AngleRadiansPerMilliSec * deltaTime;

        switch (this->mCurrentAngleDirection) {

        case AngleDirection::Up :
            if (velocity_vector.x < ignoreValue && velocity_vector.x > -ignoreValue ) break;

            if ((velocity_vector.x < 0 && velocity_vector.y <= 0 ) ||
               (velocity_vector.x < 0 && velocity_vector.y >= 0 ))
            {
                velocity_vector.Rotate(angleStepRadians);
                CurrentAngleDegrees += angleStepRadians * 180 / M_PI;

           } else if ((velocity_vector.x > 0 && velocity_vector.y >= 0 ) ||
                      (velocity_vector.x > 0 && velocity_vector.y <= 0 )){
                velocity_vector.Rotate(-angleStepRadians);
                CurrentAngleDegrees += -angleStepRadians * 180 / M_PI;
            }

            break;

        case AngleDirection::Down :
            if (velocity_vector.x < ignoreValue && velocity_vector.x > -ignoreValue ) break;

            if ((velocity_vector.x < 0 && velocity_vector.y <= 0 ) ||
               (velocity_vector.x < 0 && velocity_vector.y >= 0 ))
            {
                velocity_vector.Rotate(-angleStepRadians);
                CurrentAngleDegrees += -angleStepRadians * 180 / M_PI;

           } else if ((velocity_vector.x > 0 && velocity_vector.y >= 0 ) ||
                      (velocity_vector.x > 0 && velocity_vector.y <= 0 )){
                velocity_vector.Rotate(angleStepRadians);
                CurrentAngleDegrees += angleStepRadians * 180 / M_PI;
            }

            break;

        case AngleDirection::Left :
            if (velocity_vector.y < ignoreValue && velocity_vector.y > -ignoreValue ) break;

            if ( (velocity_vector.x <= 0 && velocity_vector.y < 0) ||
                 (velocity_vector.x >= 0 && velocity_vector.y < 0) ){
                velocity_vector.Rotate(-angleStepRadians);
                CurrentAngleDegrees += -(angleStepRadians * 180 / M_PI);
            } else if ( (velocity_vector.x <= 0 && velocity_vector.y > 0) ||
                    (velocity_vector.x >= 0 && velocity_vector.y > 0) ){
                velocity_vector.Rotate(angleStepRadians);
                CurrentAngleDegrees += angleStepRadians * 180 / M_PI;
           }
            break;

        case AngleDirection::Right :
            if (velocity_vector.y < ignoreValue && velocity_vector.y > -ignoreValue ) break;

            if ( (velocity_vector.x <= 0 && velocity_vector.y < 0) || //aristera-panw
                 (velocity_vector.x >= 0 && velocity_vector.y < 0) ){ //deksia-panw
                velocity_vector.Rotate(angleStepRadians);
                CurrentAngleDegrees += (angleStepRadians * 180 / M_PI);
            } else if ( (velocity_vector.x <= 0 && velocity_vector.y > 0) || //aristera-karw
                    (velocity_vector.x >= 0 && velocity_vector.y > 0) ){ //deksia-katw
                velocity_vector.Rotate(-angleStepRadians);
                CurrentAngleDegrees += -angleStepRadians * 180 / M_PI;
           }
            break;

        case AngleDirection::Forward:
        case AngleDirection::Backward:
        case AngleDirection::None: break;


        }//switch

        //Angle correction. It works without this but i am
        //settign back the angle in the -355 - 359 range just in
        //case so that the CurrentAngle value (double) does not get out of range (almost impossible - it is a huge number)
        if (CurrentAngleDegrees > 359){
            CurrentAngleDegrees -= 360;
        } else if (CurrentAngleDegrees < -359){
            CurrentAngleDegrees += 360;
        }

    }
}
