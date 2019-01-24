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

#include "rigid_body2d_component.h"

RigidBody2DComponent::RigidBody2DComponent()
{

}

RigidBody2DComponent RigidBody2DComponent::Clone()
{
    RigidBody2DComponent ret_rigid_body_component;
    ret_rigid_body_component.Velocity = Velocity;
    ret_rigid_body_component.AngularVelocityMagnitude =  AngularVelocityMagnitude; // degrees/ms
    ret_rigid_body_component.AngularVelocityMaximumMagnitude = AngularVelocityMaximumMagnitude ; // degrees/ms
    ret_rigid_body_component.AngularAccelerationMagnitude = AngularAccelerationMagnitude; // degrees/ms^2
    ret_rigid_body_component.TorqueMagnitude = TorqueMagnitude; // torque units
    ret_rigid_body_component.MoI = MoI; //Moment of Inertia. Set equal to mass.
    ret_rigid_body_component.Acceleration = Acceleration; // pixels/ms^2
    ret_rigid_body_component.VelocityMaximumMagnitude = VelocityMaximumMagnitude; // pixels/ms
    ret_rigid_body_component.Force = Force;
    ret_rigid_body_component.deltaRotationAngleeDegrees = deltaRotationAngleeDegrees; //the most recent rotation degrees that increased the RotationAngleDegrees
    ret_rigid_body_component.Mass = Mass;
    ret_rigid_body_component.Position = Position; //position's representational vector used in physics system calculations
    ret_rigid_body_component.RotationAngleDegrees = RotationAngleDegrees; //object's angle
    ret_rigid_body_component.isAccelerationfrozen = isAccelerationfrozen;
    ret_rigid_body_component.isAccelerationfrozen = isAngularAccelerationfrozen;

    return ret_rigid_body_component;
}
