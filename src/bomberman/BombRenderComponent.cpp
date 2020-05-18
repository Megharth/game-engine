#include "bomberman/BombRenderComponent.hpp"
#include <iostream>

BombRenderComponent::BombRenderComponent(GameObject & gameObject, SDL_Texture* b, SDL_Texture* e, double t):RenderComponent(gameObject) {
    bomb = b;
    explosion = e;
    timeout = t;
    previous = std::chrono::system_clock::now();
}

void BombRenderComponent::update(int maxFrames) {
    if(currentFrame >= maxFrames) {
        currentFrame = 0;
        currentRow = 0;
    }

    src.x = (currentFrame % 4) * 222;
    src.y = currentRow * 222;
    src.w = 222;
    src.h = 222;

    dest.x = getGameObject().x() - 20;
    dest.y = getGameObject().y() - 20;
    dest.w = getGameObject().w() + 50;
    dest.h = getGameObject().h() + 50;

    currentFrame++;

    if((currentFrame % 4) == 0 && currentFrame != 0)
        currentRow++;
}

void BombRenderComponent::render(SDL_Renderer* renderer, bool b) {
	blast = b;
	//std::cout << "blast in bombrender: "<< blast <<"\n";
    current = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = current - previous;

    if((elapsed.count() * 1000.0) >= timeout || blast) {
        update(27);
        int rv = SDL_RenderCopy(renderer, explosion, &src, &dest);
        if(rv != 0) {
            std::cout << "Some error in explosion render: " << rv << "\n";
        }

    } else {
        dest.x = getGameObject().x();
        dest.y = getGameObject().y();
        dest.w = getGameObject().w();
        dest.h = getGameObject().h();
        int rv = SDL_RenderCopy(renderer, bomb, NULL, &dest);
        if(rv != 0) {
            std::cout << "Some error in bomb render: " << rv << "\n";
        }
    }
}
