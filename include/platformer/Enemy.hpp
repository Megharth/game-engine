/*
 * Enemy.hpp
 *
 *  Created on: Mar 22, 2020
 *      Author: trive
 */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "platformer/EnemyRenderComponent.hpp"
#include <iostream>

//! \brief the Enemy game object
class Enemy : public GameObject {

public:

    Enemy(Level &, std::string, int x, int y, SDL_Renderer*);

    ~Enemy();

    void AddGravity();



private:

    std::string name;
    SDL_Texture* enemy_idle_left;
    SDL_Texture* enemy_idle_right;
    SDL_Texture* enemy_jump_left;
    SDL_Texture* enemy_jump_right;
    SDL_Texture* enemy_run_left;
    SDL_Texture* enemy_run_right;


};



#endif
