#ifndef TEXT_RENDER_COMPONENT
#define TEXT_RENDER_COMPONENT

#include "base/RenderComponent.hpp"
#include "base/GameObject.hpp"
#include "SDL.h"
#include <iostream>
//! Render the the text component
class TextRenderComponent : public RenderComponent {
public:
    TextRenderComponent(GameObject&, SDL_Texture*);
    virtual void render(SDL_Renderer*) override;    

private:
    SDL_Texture* texture;
    SDL_Rect dest;
};

#endif
