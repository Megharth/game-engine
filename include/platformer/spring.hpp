/*
 * spring.hpp
 *
 *  Created on: Mar 22, 2020
 *      Author: saite
 */

#ifndef SRC_SPRING_HPP_
#define SRC_SPRING_HPP_

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "base/RectRenderComponent.hpp"
#include <iostream>
//! \brief the spring game object
class spring : public GameObject{
public:
	spring(Level &, std::string, int, int, SDL_Renderer*);
	virtual ~spring();
private:
	SDL_Texture* springcomp;
};

#endif /* SRC_SPRING_HPP_ */
