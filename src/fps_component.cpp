#include "fps_component.h"

FpsComponent::FpsComponent()
{
    font = TTF_OpenFont("Roboto-Regular.ttf", 16);
}

FpsComponent::~FpsComponent()
{
    if(font != nullptr){
        TTF_CloseFont(font);
    }
}
