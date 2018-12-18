#ifndef FPS_ENTITY_H
#define FPS_ENTITY_H

#include "entity.h"
#include "fps_component.h"

class FpsEntity : public Entity
{
public:
    FpsEntity();

    std::unique_ptr<FpsComponent> fps_component;
};

#endif // FPS_ENTITY_H
