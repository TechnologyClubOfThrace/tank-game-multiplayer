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

#ifndef RIGID_BODY2D_COMPONENT_H
#define RIGID_BODY2D_COMPONENT_H

#include "vector2d.h"

class RigidBody2DComponent
{
public:
    RigidBody2DComponent();

    Vector2D Velocity {0,0};
    double AngularVelocityMagnitude {}; // degrees/ms
    double AngularVelocityMaximumMagnitude ; // degrees/ms
    double AngularAccelerationMagnitude {}; // degrees/ms^2
    double TorqueMagnitude {} ; // torque units
    double MoI {}; //Moment of Inertia. Set equal to mass.
    Vector2D Acceleration {0,0}; // pixels/ms^2
    double VelocityMaximumMagnitude {}; // pixels/ms
    Vector2D Force{0,0};
    double deltaRotationAngleeDegrees {}; //the most recent rotation degrees that increased the RotationAngleDegrees
    double Mass {};
    Vector2D Position {0,0}; //position's representational vector used in physics system calculations
    double RotationAngleDegrees = 0; //object's angle
    bool isAccelerationfrozen = false;
    bool isAngularAccelerationfrozen = false;

    RigidBody2DComponent Clone();
};

#endif // RIGID_BODY_COMPONENT_H
