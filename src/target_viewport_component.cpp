#include "target_viewport_component.h"

TargetViewportComponent::TargetViewportComponent(size_t targetViewportID, size_t cameraFollowerViewPortTargetIndex)
    : cameraFollowerViewPortTargetIndex(cameraFollowerViewPortTargetIndex)
{
    target_viewports.emplace_back(TargetViewport(targetViewportID));
}
