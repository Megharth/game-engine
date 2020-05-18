#ifndef BOMBERMAN_CHASEENEMY_HPP
#define BOMBERMAN_CHASEENEMY_HPP

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "bomberman/BombermanRenderComponent.hpp"
#include "base/StatesAndTransitions.hpp"
#include "base/StateComponent.hpp"

#include <iostream>

class BombermanChaseEnemy : public GameObject {
private:
    SDL_Texture
        *left, *right,
        *front, *back;

    std::string name;

public:
    BombermanChaseEnemy(Level &, std::string, int, int, SDL_Renderer*, std::weak_ptr<GameObject> player);
    virtual ~BombermanChaseEnemy();

};

#endif
