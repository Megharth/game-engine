#ifndef BALL_HPP
#define BALL_HPP

#include "SDL.h"
#include "base/GameObject.hpp"
#include "base/BlockRenderComponent.hpp"
#include <base/ResourceManager.hpp>


//! This class of game object type is the one that contains ball object.
class Ball : public GameObject {
private:
    SDL_Texture* ball;

public:
    Ball(Level &, std::string, int, int, SDL_Renderer*);
    virtual ~Ball();

};

#endif
