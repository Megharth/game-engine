/*
 * EnemyRenderComponent.cpp
 *
 *  Created on: Mar 23, 2020
 *      Author: trive
 */

#include "platformer/EnemyRenderComponent.hpp"
#include "base/PatrolComponent.hpp"

EnemyRenderComponent::EnemyRenderComponent(GameObject & gameObject,
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
	pc(gameObject.patrolComponent()),
    jump_frames(frames_jump) {}

void EnemyRenderComponent::update(int maxFrames) {
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

void EnemyRenderComponent::render(SDL_Renderer* renderer) {
    int rv = 0;

        if(pc->getright() == false) {

            rv = SDL_RenderCopy(renderer, run_left, &src, &dest);
            update(run_frames);
        }
        else if(pc->getright() == true) {

            rv = SDL_RenderCopy(renderer, run_right, &src, &dest);
            update(run_frames);
        }


    if(rv != 0)
        std::cout << "Some error in Enemy render: " << rv << "\n";
}


