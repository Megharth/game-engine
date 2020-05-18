/*
 * Boost.hpp
 *
 *  Created on: Mar 24, 2020
 *      Author: trive
 */

#ifndef BOOST_HPP
#define BOOST_HPP

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "base/RectRenderComponent.hpp"
#include <iostream>
//! \brief the boost game object
class Boost : public GameObject{
public:
	Boost(Level &, std::string, int, int, SDL_Renderer*);
	virtual ~Boost();
private:
	SDL_Texture* BoostTex;
};





#endif
