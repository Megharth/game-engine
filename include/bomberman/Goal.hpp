#ifndef GOAL_HPP
#define GOAL_HPP

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "base/BlockRenderComponent.hpp"
#include <iostream>
//! \brief The game object of the brick

class BombermanGoal: public GameObject {
private:
	SDL_Texture* texture;
public:
	BombermanGoal(Level &, std::string, int, int, SDL_Renderer*);
	virtual ~BombermanGoal();
};

#endif /* SRC_BREAKOUT_BRICK_HPP_ */
