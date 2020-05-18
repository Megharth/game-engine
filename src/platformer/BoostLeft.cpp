/*
 * BoostLeft.cpp
 *
 *  Created on: Mar 24, 2020
 *      Author: trive
 */

#include "platformer/BoostLeft.hpp"
#include "platformer/Blocks.hpp"
#include <iostream>

BoostLeft::BoostLeft(Level & level,std::string FileName, int x, int y, SDL_Renderer* renderer) :GameObject(level, x,y, 50, 30, 10) {

	BoostLeftTex = ResourceManager::getInstance().load_texture(FileName, renderer);
	setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SENSOR));
    setRenderCompenent(std::make_shared<BlockRenderComponent>(*this, BoostLeftTex));
}

BoostLeft::~BoostLeft() {

	BoostLeftTex = NULL;
}



