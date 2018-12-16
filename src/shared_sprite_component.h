#ifndef SHARED_SPRITE_COMPONENT_H
#define SHARED_SPRITE_COMPONENT_H

#include "sprite_component.h"

class SharedSpriteComponent : public SpriteComponent
{
public:
    SharedSpriteComponent();
    ~SharedSpriteComponent();

    virtual void FreeTextureMemory();
};

#endif // SHARED_SPRITE_COMPONENT_H
