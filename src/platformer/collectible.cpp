/*
 * collectible.cpp
 *
 *  Created on: Mar 18, 2020
 *      Author: saite
 */

#include "platformer/collectible.hpp"
#include "platformer/Blocks.hpp"
#include <iostream>
//#include "base/GameObject.hpp"


collectible::collectible(Level & level,std::string FileName, int x, int y, SDL_Renderer* renderer):GameObject(level, x,y, 46, 46, 6) {
	// TODO Auto-generated constructor stub
	BlockTex = ResourceManager::getInstance().load_texture(FileName, renderer);
	setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SENSOR));
	setRenderCompenent(std::make_shared<BlockRenderComponent>(*this, BlockTex));

}

collectible::~collectible() {
	BlockTex = NULL;
}

