#include "bomberman/BombermanRenderComponent.hpp"
#include "base/InputManager.hpp"

BombermanRenderComponent::BombermanRenderComponent(GameObject & gameObject,
    SDL_Texture* left_idle, SDL_Texture* right_idle, SDL_Texture* up_idle,
    SDL_Texture* down_idle, SDL_Texture* left_run, SDL_Texture* right_run,
    SDL_Texture* up_run, SDL_Texture* down_run, SDL_Texture* left_die,
    SDL_Texture* right_die, SDL_Texture* up_die, SDL_Texture* down_die,
    int frames_idle, int frames_run, int frames_die):RenderComponent(gameObject) {

    idle_left = left_idle;
    idle_right = right_idle;
    idle_front = up_idle;
    idle_back = down_idle;

    run_left = left_run;
    run_right = right_run;
    run_front = up_run;
    run_back = down_run;

    die_left = left_die;
    die_right = right_die;
    die_front = up_die;
    die_back = down_die;

    idle_frames = frames_idle;
    run_frames = frames_run;
    die_frames = frames_die;
}

void BombermanRenderComponent::update(int maxFrames) {
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

void BombermanRenderComponent::render(SDL_Renderer* renderer) {
    int rv = 0;
    GameObject & gameObject = getGameObject();
    if(!InputManager::getInstance().isBlocked()) {
        if(gameObject.running()) {
            if(gameObject.left()) {
                rv = SDL_RenderCopy(renderer, run_left, &src, &dest);
                update(run_frames);
            } 
            else if(gameObject.right()) {
                rv = SDL_RenderCopy(renderer, run_right, &src, &dest);
                update(run_frames);
            }
            else if(gameObject.up()) {
                rv = SDL_RenderCopy(renderer, run_back, &src, &dest);
                update(run_frames);
            }
            else {
                rv = SDL_RenderCopy(renderer, run_front, &src, &dest);
                update(run_frames);
            }
        }
        else {
            if(gameObject.left()) {
                rv = SDL_RenderCopy(renderer, idle_left, &src, &dest);
                update(idle_frames);
            } else if(gameObject.up()) {
                rv = SDL_RenderCopy(renderer, idle_back, &src, &dest);
                update(idle_frames);
            } else if(gameObject.down()) {
                rv = SDL_RenderCopy(renderer, idle_front, &src, &dest);
                update(idle_frames);
            }
            else {
                rv = SDL_RenderCopy(renderer, idle_right, &src, &dest);
                update(idle_frames);
            }
        }
    } else {
        if(gameObject.left()) {
            rv = SDL_RenderCopy(renderer, idle_left, &src, &dest);
            update(idle_frames);
        } else if(gameObject.up()) {
            rv = SDL_RenderCopy(renderer, idle_back, &src, &dest);
            update(idle_frames);
        } else if(gameObject.down()) {
            rv = SDL_RenderCopy(renderer, idle_front, &src, &dest);
            update(idle_frames);
        }
        else {
            rv = SDL_RenderCopy(renderer, idle_right, &src, &dest);
            update(idle_frames);
        }
    }
    if(rv != 0)
        std::cout << "Some error in bomberman render: " << rv << "\n";
}