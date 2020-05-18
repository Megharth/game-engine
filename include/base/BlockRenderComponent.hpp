#ifndef BLOCK_RENDER_COMPONENT
#define BLOCK_RENDER_COMPONENT

#include "base/RenderComponent.hpp"
#include "base/GameObject.hpp"
#include "SDL.h"
#include <iostream>
//! render the blocks
class BlockRenderComponent : public RenderComponent {
public:
    BlockRenderComponent(GameObject&, SDL_Texture*);
    virtual void render(SDL_Renderer*) override;    

private:
    SDL_Texture* texture;
    SDL_Rect dest;
};

#endif
