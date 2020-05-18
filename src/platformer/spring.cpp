/*
 * spring.cpp
 *
 *  Created on: Mar 22, 2020
 *      Author: saite
 */

#include "platformer/spring.hpp"
#include "platformer/Blocks.hpp"
#include <iostream>

spring::spring(Level & level,std::string FileName, int x, int y, SDL_Renderer* renderer) :GameObject(level, x,y, 64, 26, 7) {
	// TODO Auto-generated constructor stub
	springcomp = ResourceManager::getInstance().load_texture(FileName, renderer);
	setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SENSOR));
    setRenderCompenent(std::make_shared<BlockRenderComponent>(*this, springcomp));
}

spring::~spring() {
	// TODO Auto-generated destructor stub
	springcomp = NULL;
}

