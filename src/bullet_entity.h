#ifndef BULLET_ENTITY_H
#define BULLET_ENTITY_H

#include "entity.h"
#include "render_utils.h"

class BulletEntity : public Entity
{
public:
    BulletEntity();

private:
    static SpriteComponent m_bullet_sprite_component;
};

#endif // BULLET_ENTITY_H
