#ifndef BOMB_HPP
#define BOMB_HPP

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "bomberman/BombRenderComponent.hpp"
#include "bomberman/ExplosionComponent.hpp"
#include <iostream>

class Bomb: public GameObject {
private:
    bool explode{false};
    SDL_Texture* bomb;
    SDL_Texture* explosion;

public:
    Bomb(Level &, std::string, int, int, SDL_Renderer*);
    virtual ~Bomb();

    inline void blast() { explode = true; };

};

#endif