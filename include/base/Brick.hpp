/*
 * Brick.hpp
 *
 *  Created on: Mar 29, 2020
 *      Author: saite
 */

#ifndef SRC_BREAKOUT_BRICK_HPP_
#define SRC_BREAKOUT_BRICK_HPP_

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "base/BlockRenderComponent.hpp"
#include <iostream>
//! \brief The game object of the brick

class Brick: public GameObject {
private:
	SDL_Texture* BrickTex;
	bool strong;
public:
	Brick(Level &, std::string, bool, int, int, int, int, int, SDL_Renderer*);
	inline bool isStrong() { return strong; }
	virtual ~Brick();
};

#endif /* SRC_BREAKOUT_BRICK_HPP_ */
