#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "viewport.h"
#include "entity.h"

class CollisionSystem
{
public:
    CollisionSystem();
    static void DetectAndRespond(const Entity &entity);
};

#endif // COLLISION_SYSTEM_H
