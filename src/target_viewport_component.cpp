#include "target_viewport_component.h"

TargetViewportComponent::TargetViewportComponent(size_t targetViewportID)
{
    target_viewports.emplace_back(TargetViewport(targetViewportID));
}
