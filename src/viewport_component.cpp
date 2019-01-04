#include "viewport_component.h"

ViewportComponent::ViewportComponent(size_t viewportID)
{
    viewports.emplace_back(ViewportTarget(viewportID));
}
