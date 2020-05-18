#include "platformer/PlayerRenderComponent.hpp"
#include "platformer/InputComponent.hpp"
#include "iostream"

PlayerRenderComponent::PlayerRenderComponent(GameObject & gameObject, 
    SDL_Texture* right,
    SDL_Texture* left,
    SDL_Texture* right_run,
    SDL_Texture* left_run,
    SDL_Texture* right_jump,
    SDL_Texture* left_jump,
    int frames_idle, int frames_run, int frames_jump):
    RenderComponent(gameObject), 
    idle_right(right),
    idle_left(left),
    run_right(right_run),
    run_left(left_run),
    jump_right(right_jump),
    jump_left(left_jump),
    idle_frames(frames_idle),
    run_frames(frames_run),
    jump_frames(frames_jump),
    left(false) {}

void PlayerRenderComponent::update(int maxFrames) {
    if(currentFrame >= maxFrames) {
        currentFrame = 0;
        currentRow = 0;
    }
    
    src.x = (currentFrame % 4) * 128;
    src.y = currentRow * 128;
    src.w = 128;
    src.h = 128;

    dest.x = getGameObject().x();
    dest.y = getGameObject().y();
    dest.w = getGameObject().w();
    dest.h = getGameObject().h();
    currentFrame++;

    if((currentFrame % 4) == 0 && currentFrame != 0)
        currentRow++;
}

void PlayerRenderComponent::render(SDL_Renderer* renderer) {
    int rv = 0;
    if(!InputManager::getInstance().isBlocked()) {
        if(InputManager::getInstance().isKeyDown(SDLK_LEFT)) {
            left = true;
            rv = SDL_RenderCopy(renderer, run_left, &src, &dest);
            update(run_frames);
        } 
        else if(InputManager::getInstance().isKeyDown(SDLK_RIGHT)) {
            left = false;
            rv = SDL_RenderCopy(renderer, run_right, &src, &dest);
            update(run_frames);
        }
        else if(InputManager::getInstance().isKeyDown(SDLK_UP)) {
            if(left)
                rv = SDL_RenderCopy(renderer, jump_left, &src, &dest);
            else
                rv = SDL_RenderCopy(renderer, jump_right, &src, &dest);
            update(jump_frames);
        }
        else {
            if(left) {
                rv = SDL_RenderCopy(renderer, idle_left, &src, &dest);
            } else {
                rv = SDL_RenderCopy(renderer, idle_right, &src, &dest);
            }
            update(idle_frames);
        }
    } else {
        if(left) {
            rv = SDL_RenderCopy(renderer, idle_left, &src, &dest);
        } else {
            rv = SDL_RenderCopy(renderer, idle_right, &src, &dest);
        }
        update(idle_frames);
    }
    if(rv != 0)
        std::cout << "Some error in Player render: " << rv << "\n";
}
