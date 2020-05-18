
#ifndef GOAL_HPP
#define GOAL_HPP

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include <base/BlockRenderComponent.hpp>
#include <platformer/GoalCollide.hpp>
//! \brief the Goal game object
class Goal : public GameObject {
private:
    SDL_Texture* texture;

public:
    Goal(Level &, std::string, int, int, SDL_Renderer*);
    ~Goal();
};

#endif
