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

#ifndef TANK_INPUT_SYSTEM_H
#define TANK_INPUT_SYSTEM_H

#include <SDL.h>
#include "tank_input_component.h"
#include "rigid_body2d_component.h"
#include "transform_component.h"
#include "bullet_entity.h"
#include "point_collider2d.h"

class TankInputSystem
{
public:
    TankInputSystem(); 
    static void HandleEvent(const SDL_Event &e, const Entity &entity);

private:
    static void ApplyRightTorque(RigidBody2DComponent &rigidBody2dComponent);
    static void ApplyLeftTorque(RigidBody2DComponent &rigidBody2dComponent);
    static void ApplyForwardForce(RigidBody2DComponent &rigidBody2dComponent);
    static void ApplyBackwardsForce(RigidBody2DComponent &rigidBody2dComponent);
    static void KillTorque(RigidBody2DComponent &rigidBody2dComponent);
    static void KillForce(RigidBody2DComponent &rigidBody2dComponent);
    static void FireBullet(const Entity &entity);
};

#endif // TANK_INPUT_SYSTEM_H
