#ifndef SHARED_SPRITE_COMPONENT_H
#define SHARED_SPRITE_COMPONENT_H

#include "sprite_component.h"

class SharedSpriteComponent : public SpriteComponent
{
public:
    SharedSpriteComponent();
    ~SharedSpriteComponent() override;

protected:
    void FreeTextureMemory() override;
};

#endif // SHARED_SPRITE_COMPONENT_H
