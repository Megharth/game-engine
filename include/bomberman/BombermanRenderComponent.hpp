#ifndef BOMBERMAN_RENDER_COMPONENT
#define BOMBERMAN_RENDER_COMPONENT

#include <SDL.h>
#include "base/RenderComponent.hpp"
#include "base/GameObject.hpp"

class BombermanRenderComponent : public RenderComponent {
public:
    BombermanRenderComponent(GameObject &, 
    SDL_Texture*,SDL_Texture*,SDL_Texture*,
    SDL_Texture*,SDL_Texture*,SDL_Texture*, 
    SDL_Texture*,SDL_Texture*,SDL_Texture*, 
    SDL_Texture*,SDL_Texture*,SDL_Texture*, 
    int, int, int);

    virtual void render(SDL_Renderer*) override;

    void update(int);

private:
    SDL_Texture 
        *idle_right, 
        *idle_left,
        *idle_front,
        *idle_back,
        *run_right,
        *run_left,
        *run_front,
        *run_back,
        *die_right,
        *die_left,
        *die_front,
        *die_back;
    int currentFrame{0};
    int 
        idle_frames,
        run_frames,
        die_frames
    ;
    int currentRow{0};
    SDL_Rect src;
    SDL_Rect dest;

};

#endif