#ifndef TARGET_VIEWPORT_COMPONENT_H
#define TARGET_VIEWPORT_COMPONENT_H

#include <vector>
#include <limits>
#include "target_viewport.h"

class TargetViewportComponent
{
public:
    TargetViewportComponent(size_t targetViewportID, size_t cameraFollowerViewPortTargetIndex = std::numeric_limits<size_t>::max());
    std::vector<TargetViewport> target_viewports;
    size_t cameraFollowerViewPortTargetIndex;
};

#endif // TARGET_VIEWPORT_COMPONENT_H
