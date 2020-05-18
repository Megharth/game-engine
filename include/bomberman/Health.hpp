#ifndef HEALTH_HPP
#define HEALTH_HPP

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "base/BlockRenderComponent.hpp"
#include <iostream>
//! \brief The game object of the brick

class BombermanHealth: public GameObject {
private:
	SDL_Texture* texture;
public:
	BombermanHealth(Level &, std::string, int, int, SDL_Renderer*);
	virtual ~BombermanHealth();
};

#endif /* SRC_BREAKOUT_BRICK_HPP_ */
