#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "bomberman/BombermanRenderComponent.hpp"
#include <iostream>

class Player : public GameObject {
private:
    std::string name;
    SDL_Texture* idle_front;
    SDL_Texture* idle_back;
    SDL_Texture* idle_left;
    SDL_Texture* idle_right;
    SDL_Texture* run_front;
    SDL_Texture* run_back;
    SDL_Texture* run_left;
    SDL_Texture* run_right;
    SDL_Texture* die_front;
    SDL_Texture* die_back;
    SDL_Texture* die_left;
    SDL_Texture* die_right;

public:
    Player(Level&, std::string, int, int, SDL_Renderer*);

    virtual ~Player();
    
};

#endif