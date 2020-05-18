#ifndef PLAYER_RENDER_COMPONENT
#define PLAYER_RENDER_COMPONENT

#include "base/RenderComponent.hpp"
#include "base/GameObject.hpp"
#include "SDL.h"
//! \brief used to render player component
class PlayerRenderComponent : public RenderComponent {
public: 
    PlayerRenderComponent(GameObject&, 
        SDL_Texture*,
        SDL_Texture*,
        SDL_Texture*,
        SDL_Texture*,
        SDL_Texture*,
        SDL_Texture*,
        int, int, int);
    /**
     * render the player updated from spritesheet
     */
    virtual void render(SDL_Renderer * renderer) override;
    /**
     * Update the player from the spritesheet
     */
    void update(int);

private:
    SDL_Texture 
        *idle_right, 
        *idle_left,
        *run_right,
        *run_left,
        *jump_right,
        *jump_left;
    int currentFrame{0};
    int 
        idle_frames,
        run_frames,
        jump_frames
    ;
    bool left;
    int currentRow{0};
    SDL_Rect src;
    SDL_Rect dest;
};

#endif
