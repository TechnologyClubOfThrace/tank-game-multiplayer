#ifndef TARGET_VIEWPORT_COMPONENT_H
#define TARGET_VIEWPORT_COMPONENT_H

#include <vector>
#include "target_viewport.h"

class TargetViewportComponent
{
public:
    TargetViewportComponent(size_t targetViewportID);
    bool movesTheCamera = false;
    std::vector<TargetViewport> target_viewports;
};

#endif // TARGET_VIEWPORT_COMPONENT_H
