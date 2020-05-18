#ifndef TEXTURE_RENDERER_COMPONENT
#define TEXTURE_RENDERER_COMPONENT

#include "base/RenderComponent.hpp"
#include "SDL.h"
//! \brief Render the Texture component
class TextureRendererComponent : public RenderComponent {
public: 
    TextureRendererComponent(GameObject&, SDL_Texture*);
    void render(SDL_Renderer * renderer) override;

private:
    SDL_Texture* texture;
};

#endif
