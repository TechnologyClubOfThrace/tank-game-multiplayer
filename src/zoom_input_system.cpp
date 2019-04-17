#include "zoom_input_system.h"
#include "game.h"

ZoomInputSystem::ZoomInputSystem()
{

}

void ZoomInputSystem::Update(const double &deltaTime, const Entity& entity)
{
    auto old_entityScale = game::viewports[entity.zoom_input_component->viewportIndex].entityScale;

    switch (entity.zoom_input_component->zoomState){

    case ZoomState::noZoom:
        break;

    case ZoomState::zoomIn:
        game::viewports[entity.zoom_input_component->viewportIndex].entityScale.x += deltaTime * entity.zoom_input_component->zoomSpeed;
        game::viewports[entity.zoom_input_component->viewportIndex].entityScale.y += deltaTime * entity.zoom_input_component->zoomSpeed;
        break;

    case ZoomState::zoomOut:
        game::viewports[entity.zoom_input_component->viewportIndex].entityScale.x -= deltaTime * entity.zoom_input_component->zoomSpeed;
        game::viewports[entity.zoom_input_component->viewportIndex].entityScale.y -= deltaTime * entity.zoom_input_component->zoomSpeed;
        break;

    case ZoomState::keepZoom:
        break;

    case ZoomState::resetZoom:
        double resetSpeed =
                game::viewports[entity.zoom_input_component->viewportIndex].entityScale.x < 1 ?
                    entity.zoom_input_component->zoomResetSpeed : -entity.zoom_input_component->zoomResetSpeed;
        if ( ((game::viewports[entity.zoom_input_component->viewportIndex].entityScale.x) > 0.98) &&
             ((game::viewports[entity.zoom_input_component->viewportIndex].entityScale.x) < 1.02)) {
            game::viewports[entity.zoom_input_component->viewportIndex].entityScale = {1, 1};
            entity.zoom_input_component->zoomState = ZoomState::noZoom;
        } else {
            game::viewports[entity.zoom_input_component->viewportIndex].entityScale.x += deltaTime * resetSpeed;
            game::viewports[entity.zoom_input_component->viewportIndex].entityScale.y += deltaTime * resetSpeed;
        }
        break;
    }


    if ((game::viewports[entity.zoom_input_component->viewportIndex].entityScale.x *
           ViewPort::levelWidth < game::viewports[entity.zoom_input_component->viewportIndex].frame.w) ||
         (game::viewports[entity.zoom_input_component->viewportIndex].entityScale.y *
           ViewPort::levelHeight < game::viewports[entity.zoom_input_component->viewportIndex].frame.h)){
        game::viewports[entity.zoom_input_component->viewportIndex].entityScale = old_entityScale;
    }


}

void ZoomInputSystem::HandleEvent(const SDL_Event& e, const Entity& entity)
{
    switch (entity.zoom_input_component->zoomState){

    case ZoomState::noZoom:
        switch(e.key.keysym.sym )
        {
        case SDLK_EQUALS:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                entity.zoom_input_component->zoomState = ZoomState::zoomIn;
            }
            break;
        case SDLK_MINUS:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                entity.zoom_input_component->zoomState = ZoomState::zoomOut;
            }
            break;
        }
        break;

    case ZoomState::zoomIn:
        switch(e.key.keysym.sym )
        {
        case SDLK_EQUALS:
            if( e.type == SDL_KEYUP ){
                entity.zoom_input_component->zoomState = ZoomState::keepZoom;
            }
            break;
        case SDLK_MINUS:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                entity.zoom_input_component->zoomState = ZoomState::resetZoom;
            }
            break;
        }
        break;

    case ZoomState::zoomOut:
        switch(e.key.keysym.sym )
        {
        case SDLK_MINUS:
            if( e.type == SDL_KEYUP ){
                entity.zoom_input_component->zoomState = ZoomState::keepZoom;
            }
            break;
        case SDLK_EQUALS:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                entity.zoom_input_component->zoomState = ZoomState::resetZoom;
            }
            break;
        }
        break;

    case ZoomState::keepZoom:
        switch(e.key.keysym.sym )
        {
        case SDLK_MINUS:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                entity.zoom_input_component->zoomState = ZoomState::zoomOut;
            }
            break;
        case SDLK_EQUALS:
            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                entity.zoom_input_component->zoomState = ZoomState::zoomIn;
            }
            break;
        }
        break;

    case ZoomState::resetZoom:
        break;
    }
}
