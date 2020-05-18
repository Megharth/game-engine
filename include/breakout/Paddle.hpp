#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "base/BlockRenderComponent.hpp"
#include <iostream>
//! \brief The paddle game object
class Paddle : public GameObject {
private:
    SDL_Texture* paddle;

public:
    Paddle(Level &, std::string, int, int, SDL_Renderer*);
    virtual ~Paddle();
};


#endif
