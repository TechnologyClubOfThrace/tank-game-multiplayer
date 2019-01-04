#ifndef ZOOM_INPUT_COMPONENT_H
#define ZOOM_INPUT_COMPONENT_H

#include <cstddef>

enum class ZoomState
{
    noZoom,
    zoomIn,
    zoomOut,
    keepZoom,
    resetZoom
};

class ZoomInputComponent
{
public:
    ZoomInputComponent(size_t viewportIndex);

    ZoomState zoomState = ZoomState::noZoom;
    double zoomSpeed = 0.0005;
    double zoomResetSpeed = 0.0020;
    size_t viewportIndex;
};

#endif // ZOOM_INPUT_COMPONENT_H
