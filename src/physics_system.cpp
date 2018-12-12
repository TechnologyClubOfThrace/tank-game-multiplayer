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

#include "physics_system.h"
#include <math.h>

PhysicsSystem::PhysicsSystem()
{

}

void PhysicsSystem::Update(const std::chrono::milliseconds::rep &deltaTime,
                           TransformComponent &transformComponent,
                           const TankInputComponent &tankInputComponent,
                           RigidBody2DComponent &rigidBody2dComponent)
{
    switch (tankInputComponent.state) {
    case State::stopped:
        break;

    case State::stoppedRotationClockwise:
        {
        rigidBody2dComponent.AngularAccelerationMagnitude = rigidBody2dComponent.TorqueMagnitude / rigidBody2dComponent.MoI;

        if(!rigidBody2dComponent.isAngularAccelerationfrozen){
            if(rigidBody2dComponent.AngularVelocityMagnitude < rigidBody2dComponent.AngularVelocityMaximumMagnitude){
                rigidBody2dComponent.AngularVelocityMagnitude += rigidBody2dComponent.AngularAccelerationMagnitude * static_cast<double>(deltaTime);
                if(rigidBody2dComponent.AngularVelocityMagnitude > rigidBody2dComponent.AngularVelocityMaximumMagnitude){
                    rigidBody2dComponent.AngularVelocityMagnitude = rigidBody2dComponent.AngularVelocityMaximumMagnitude;
                    rigidBody2dComponent.isAngularAccelerationfrozen=true;
                }
            }
        }

        transformComponent.RotationAngleDegrees +=
                rigidBody2dComponent.AngularVelocityMagnitude * static_cast<double>(deltaTime)
                + 0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * static_cast<double>(deltaTime * deltaTime);
        }
        break;


    case State::stoppedRotationCounterClockwise:
        {
        rigidBody2dComponent.AngularAccelerationMagnitude = rigidBody2dComponent.TorqueMagnitude / rigidBody2dComponent.MoI;

        if(!rigidBody2dComponent.isAngularAccelerationfrozen){
            if(rigidBody2dComponent.AngularVelocityMagnitude < rigidBody2dComponent.AngularVelocityMaximumMagnitude){
                rigidBody2dComponent.AngularVelocityMagnitude += rigidBody2dComponent.AngularAccelerationMagnitude * static_cast<double>(deltaTime);
                if(rigidBody2dComponent.AngularVelocityMagnitude > rigidBody2dComponent.AngularVelocityMaximumMagnitude){
                    rigidBody2dComponent.AngularVelocityMagnitude = rigidBody2dComponent.AngularVelocityMaximumMagnitude;
                    rigidBody2dComponent.isAngularAccelerationfrozen=true;
                }
            }
        }

        transformComponent.RotationAngleDegrees +=
                rigidBody2dComponent.AngularVelocityMagnitude * static_cast<double>(deltaTime)
                - 0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * static_cast<double>(deltaTime * deltaTime);
        }
        break;

    case State::moveForward:
    {
        if(!rigidBody2dComponent.isAccelerationfrozen){
            if(rigidBody2dComponent.Velocity.Magnitude() < rigidBody2dComponent.MaxVelocityMagnitude){
                rigidBody2dComponent.Velocity += rigidBody2dComponent.Acceleration * static_cast<double>(deltaTime);
                if(rigidBody2dComponent.Velocity.Magnitude() > rigidBody2dComponent.MaxVelocityMagnitude){
                    rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.MaxVelocityMagnitude);
                    rigidBody2dComponent.isAccelerationfrozen=true;
                }
            }
        }

        transformComponent.Position += rigidBody2dComponent.Velocity * static_cast<double>(deltaTime);
    }
    break;

    case State::moveBackwards:
    {
        if(!rigidBody2dComponent.isAccelerationfrozen){
            if(rigidBody2dComponent.Velocity.Magnitude() < rigidBody2dComponent.MaxVelocityMagnitude){
                rigidBody2dComponent.Velocity += rigidBody2dComponent.Acceleration * static_cast<double>(deltaTime);
                if(rigidBody2dComponent.Velocity.Magnitude() > rigidBody2dComponent.MaxVelocityMagnitude){
                    rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.MaxVelocityMagnitude);
                    rigidBody2dComponent.isAccelerationfrozen = true;
                }
            }

        }

        transformComponent.Position -= rigidBody2dComponent.Velocity * static_cast<double>(deltaTime);
    }
    break;

    case State::forwardRotationClockwise:
    {
        //rotation
        rigidBody2dComponent.AngularAccelerationMagnitude = rigidBody2dComponent.TorqueMagnitude / rigidBody2dComponent.MoI;

        if(!rigidBody2dComponent.isAngularAccelerationfrozen){
            if(rigidBody2dComponent.AngularVelocityMagnitude < rigidBody2dComponent.AngularVelocityMaximumMagnitude){
                rigidBody2dComponent.AngularVelocityMagnitude += rigidBody2dComponent.AngularAccelerationMagnitude * static_cast<double>(deltaTime);
                if(rigidBody2dComponent.AngularVelocityMagnitude > rigidBody2dComponent.AngularVelocityMaximumMagnitude){
                    rigidBody2dComponent.AngularVelocityMagnitude = rigidBody2dComponent.AngularVelocityMaximumMagnitude;
                    rigidBody2dComponent.isAngularAccelerationfrozen=true;
                }
            }
        }

        transformComponent.RotationAngleDegrees +=
                rigidBody2dComponent.AngularVelocityMagnitude * static_cast<double>(deltaTime)
                + 0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * static_cast<double>(deltaTime * deltaTime);

        //forward
        if(!rigidBody2dComponent.isAccelerationfrozen){
            if(rigidBody2dComponent.Velocity.Magnitude() < rigidBody2dComponent.MaxVelocityMagnitude){
                rigidBody2dComponent.Velocity += rigidBody2dComponent.Acceleration * static_cast<double>(deltaTime);
                if(rigidBody2dComponent.Velocity.Magnitude() > rigidBody2dComponent.MaxVelocityMagnitude){
                    rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.MaxVelocityMagnitude);
                    rigidBody2dComponent.isAccelerationfrozen=true;
                }
            }
        }

        transformComponent.Position += rigidBody2dComponent.Velocity * static_cast<double>(deltaTime);
        }
        break;

    case State::forwardRotationCounterClockwise:
    {
        //rotation
        rigidBody2dComponent.AngularAccelerationMagnitude = rigidBody2dComponent.TorqueMagnitude / rigidBody2dComponent.MoI;

        if(!rigidBody2dComponent.isAngularAccelerationfrozen){
            if(rigidBody2dComponent.AngularVelocityMagnitude < rigidBody2dComponent.AngularVelocityMaximumMagnitude){
                rigidBody2dComponent.AngularVelocityMagnitude += rigidBody2dComponent.AngularAccelerationMagnitude * static_cast<double>(deltaTime);
                if(rigidBody2dComponent.AngularVelocityMagnitude > rigidBody2dComponent.AngularVelocityMaximumMagnitude){
                    rigidBody2dComponent.AngularVelocityMagnitude = rigidBody2dComponent.AngularVelocityMaximumMagnitude;
                    rigidBody2dComponent.isAngularAccelerationfrozen=true;
                }
            }
        }

        transformComponent.RotationAngleDegrees +=
                rigidBody2dComponent.AngularVelocityMagnitude * static_cast<double>(deltaTime)
                - 0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * static_cast<double>(deltaTime * deltaTime);

        //forward
        if(!rigidBody2dComponent.isAccelerationfrozen){
            if(rigidBody2dComponent.Velocity.Magnitude() < rigidBody2dComponent.MaxVelocityMagnitude){
                rigidBody2dComponent.Velocity += rigidBody2dComponent.Acceleration * static_cast<double>(deltaTime);
                if(rigidBody2dComponent.Velocity.Magnitude() > rigidBody2dComponent.MaxVelocityMagnitude){
                    rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.MaxVelocityMagnitude);
                    rigidBody2dComponent.isAccelerationfrozen=true;
                }
            }
        }

        transformComponent.Position += rigidBody2dComponent.Velocity * static_cast<double>(deltaTime);
        }
        break;

    case State::backwardsRotationClockwise:
    {
        //rotation
        rigidBody2dComponent.AngularAccelerationMagnitude = rigidBody2dComponent.TorqueMagnitude / rigidBody2dComponent.MoI;

        if(!rigidBody2dComponent.isAngularAccelerationfrozen){
            if(rigidBody2dComponent.AngularVelocityMagnitude < rigidBody2dComponent.AngularVelocityMaximumMagnitude){
                rigidBody2dComponent.AngularVelocityMagnitude += rigidBody2dComponent.AngularAccelerationMagnitude * static_cast<double>(deltaTime);
                if(rigidBody2dComponent.AngularVelocityMagnitude > rigidBody2dComponent.AngularVelocityMaximumMagnitude){
                    rigidBody2dComponent.AngularVelocityMagnitude = rigidBody2dComponent.AngularVelocityMaximumMagnitude;
                    rigidBody2dComponent.isAngularAccelerationfrozen=true;
                }
            }
        }

        transformComponent.RotationAngleDegrees +=
                rigidBody2dComponent.AngularVelocityMagnitude * static_cast<double>(deltaTime)
                + 0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * static_cast<double>(deltaTime * deltaTime);

        //forward
        if(!rigidBody2dComponent.isAccelerationfrozen){
            if(rigidBody2dComponent.Velocity.Magnitude() < rigidBody2dComponent.MaxVelocityMagnitude){
                rigidBody2dComponent.Velocity += rigidBody2dComponent.Acceleration * static_cast<double>(deltaTime);
                if(rigidBody2dComponent.Velocity.Magnitude() > rigidBody2dComponent.MaxVelocityMagnitude){
                    rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.MaxVelocityMagnitude);
                    rigidBody2dComponent.isAccelerationfrozen=true;
                }
            }
        }

        transformComponent.Position -= rigidBody2dComponent.Velocity * static_cast<double>(deltaTime);
        }
        break;

    case State::backwardsRotationCounterClockwise:
    {
        //rotation
        rigidBody2dComponent.AngularAccelerationMagnitude = rigidBody2dComponent.TorqueMagnitude / rigidBody2dComponent.MoI;

        if(!rigidBody2dComponent.isAngularAccelerationfrozen){
            if(rigidBody2dComponent.AngularVelocityMagnitude < rigidBody2dComponent.AngularVelocityMaximumMagnitude){
                rigidBody2dComponent.AngularVelocityMagnitude += rigidBody2dComponent.AngularAccelerationMagnitude * static_cast<double>(deltaTime);
                if(rigidBody2dComponent.AngularVelocityMagnitude > rigidBody2dComponent.AngularVelocityMaximumMagnitude){
                    rigidBody2dComponent.AngularVelocityMagnitude = rigidBody2dComponent.AngularVelocityMaximumMagnitude;
                    rigidBody2dComponent.isAngularAccelerationfrozen=true;
                }
            }
        }

        transformComponent.RotationAngleDegrees +=
                rigidBody2dComponent.AngularVelocityMagnitude * static_cast<double>(deltaTime)
                - 0.5 * rigidBody2dComponent.AngularAccelerationMagnitude * static_cast<double>(deltaTime * deltaTime);

        //forward
        if(!rigidBody2dComponent.isAccelerationfrozen){
            if(rigidBody2dComponent.Velocity.Magnitude() < rigidBody2dComponent.MaxVelocityMagnitude){
                rigidBody2dComponent.Velocity += rigidBody2dComponent.Acceleration * static_cast<double>(deltaTime);
                if(rigidBody2dComponent.Velocity.Magnitude() > rigidBody2dComponent.MaxVelocityMagnitude){
                    rigidBody2dComponent.Velocity.SetMagnitude(rigidBody2dComponent.MaxVelocityMagnitude);
                    rigidBody2dComponent.isAccelerationfrozen=true;
                }
            }
        }

        transformComponent.Position -= rigidBody2dComponent.Velocity * static_cast<double>(deltaTime);
        }
        break;

    }//switch

}
