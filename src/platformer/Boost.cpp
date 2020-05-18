/*
 * Boost.cpp
 *
 *  Created on: Mar 24, 2020
 *      Author: trive
 */


#include "platformer/Boost.hpp"
#include "platformer/Blocks.hpp"
#include <iostream>

Boost::Boost(Level & level,std::string FileName, int x, int y, SDL_Renderer* renderer) :GameObject(level, x,y, 50, 30, 8) {

	BoostTex = ResourceManager::getInstance().load_texture(FileName, renderer);
	setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SENSOR));
    setRenderCompenent(std::make_shared<BlockRenderComponent>(*this, BoostTex));
}

Boost::~Boost() {

	BoostTex = NULL;
}

