#ifndef BOMBERMAN_ENEMY_HPP
#define BOMBERMAN_ENEMY_HPP

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "bomberman/BombermanRenderComponent.hpp"
#include <iostream>

class BombermanEnemy : public GameObject {
private:
    SDL_Texture
        *left, *right,
        *front, *back;
    
    std::string name;

public:
    BombermanEnemy(Level &, std::string, int, int, SDL_Renderer*);
    virtual ~BombermanEnemy();

};

#endif