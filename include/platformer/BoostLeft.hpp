/*
 * BoostLeft.hpp
 *
 *  Created on: Mar 24, 2020
 *      Author: trive
 */

#ifndef BOOSTLEFT_HPP
#define BOOSTLEFT_HPP

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "base/RectRenderComponent.hpp"
#include <iostream>
//! \brief the boost game object
class BoostLeft : public GameObject{
public:
	BoostLeft(Level &, std::string, int, int, SDL_Renderer*);
	virtual ~BoostLeft();
private:
	SDL_Texture* BoostLeftTex;
};




#endif /* INCLUDE_BOOSTLEFT_HPP_ */
