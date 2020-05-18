/*
 * collectible.hpp
 *
 *  Created on: Mar 18, 2020
 *      Author: saite
 */

#ifndef SRC_COLLECTIBLE_HPP_
#define SRC_COLLECTIBLE_HPP_

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "base/RectRenderComponent.hpp"
#include <iostream>
//! \brief the collectible game object
class collectible : public GameObject{
public:
	collectible(Level &, std::string, int, int, SDL_Renderer*);
	virtual ~collectible();

private:
	SDL_Texture* BlockTex;
};

#endif /* SRC_COLLECTIBLE_HPP_ */
