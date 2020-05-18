#include "base/BlockRenderComponent.hpp"
#include "base/ResourceManager.hpp"

BlockRenderComponent::BlockRenderComponent(GameObject & gameObject, SDL_Texture* tex):
    RenderComponent(gameObject),
    texture(tex) {}

void BlockRenderComponent::render(SDL_Renderer* renderer) {
    dest.x = getGameObject().x();
    dest.y = getGameObject().y();
    dest.w = getGameObject().w();
    dest.h = getGameObject().h();
    if(getGameObject().tag() == 5 && getGameObject().isCollectibleVisible()) {
        SDL_Texture* goal = ResourceManager::getInstance().load_texture("bomberman/goal.png", renderer);
        dest.w = dest.h;
        int rv = SDL_RenderCopy(renderer, goal, NULL, &dest);
        if(rv != 0) {
            std::cout << "Some error in Block render: " << rv << "\n";
        }
    } else if(getGameObject().tag() == 6 && getGameObject().isCollectibleVisible()) {
        SDL_Texture* health = ResourceManager::getInstance().load_texture("bomberman/health.png", renderer);
        dest.w = 50;
        dest.h = 35;
        int rv = SDL_RenderCopy(renderer, health, NULL, &dest);
        if(rv != 0) {
            std::cout << "Some error in Block render: " << rv << "\n";
        }
    } else {
        int rv = SDL_RenderCopy(renderer, texture, NULL, &dest);
        if(rv != 0) {
           std::cout << "Some error in Block render: " << rv << "\n";
        }
    }

    
}
