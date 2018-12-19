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

#include "tank_entity.h"

TankEntity::TankEntity()
{
    //create required components for the tank entity
    transform_component = std::make_unique<TransformComponent>();//transform / position related
    sprite_component = std::make_unique<SpriteComponent>();//appearance - rendering system,
    tank_input_component = std::make_unique<TankInputComponent>();//player input handling - state machine
    rigid_body2d_component = std::make_unique<RigidBody2DComponent>();//physics
    collider2d_collection_component = std::make_unique<Collider2DCollectionComponent>();//collision shapes
    viewport_component = std::make_unique<ViewportComponent>();//alternative viewport rendering

    viewport_component->viewportID = 1;
}
