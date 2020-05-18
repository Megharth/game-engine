/*
 * Blocks.cpp
 *
 *  Created on: Feb 27, 2020
 *      Author: trive
 */

#include "platformer/Blocks.hpp"
#include <iostream>

Block::Block(Level & level, std::string FileName, int x, int y, SDL_Renderer* renderer):GameObject(level, x, y, 64, 36, 9) {
	BlockTex = ResourceManager::getInstance().load_texture(FileName, renderer);
	setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SOLID));
	setRenderCompenent(std::make_shared<BlockRenderComponent>(*this, BlockTex));
}

Block::~Block(){
	BlockTex = NULL;
}