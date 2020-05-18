#ifndef BOMB_RENDER_COMPONENT
#define BOMB_RENDER_COMPONENT

#include <SDL.h>
#include "base/RenderComponent.hpp"
#include "base/GameObject.hpp"
#include <chrono>

class BombRenderComponent : public RenderComponent {
private:
    SDL_Texture* bomb;
    SDL_Texture* explosion;
    double timeout; 
    std::chrono::system_clock::time_point previous, current;
    SDL_Rect src, dest;
    int currentFrame{0};
    int currentRow{0};
    bool blast = false;

public:
    BombRenderComponent(GameObject &, SDL_Texture*, SDL_Texture*, double);

    virtual void render(SDL_Renderer*, bool) override;

    void update(int);

};

#endif
