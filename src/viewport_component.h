#ifndef VIEWPORT_COMPONENT_H
#define VIEWPORT_COMPONENT_H

#include <vector>
#include "viewport_target.h"

class ViewportComponent
{
public:
    ViewportComponent(size_t viewportID);

    std::vector<ViewportTarget> viewports;
};

#endif // VIEWPORT_COMPONENT_H
