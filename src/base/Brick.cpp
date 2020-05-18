/*
 * Brick.cpp
 *
 *  Created on: Mar 29, 2020
 *      Author: saite
 */

#include "base/Brick.hpp"
#include "base/GameObject.hpp"
#include <iostream>

Brick::Brick(Level & level,std::string FileName, bool mStrong, int x, int y, int w, int h, int solid, SDL_Renderer* renderer):GameObject(level, x,y, w, h, 3) {
	// TODO Auto-generated constructor stub
	strong = mStrong;
	if(strong)
		this->setStrong(true);
	BrickTex = ResourceManager::getInstance().load_texture(FileName, renderer);
	if(solid)
    	setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SOLID));
	else
    	setPhysicsCompenent(std::make_shared<PhysicsComponent>(*this, PhysicsComponent::Type::STATIC_SENSOR));
	setRenderCompenent(std::make_shared<BlockRenderComponent>(*this, BrickTex));

}

Brick::~Brick() {
	// TODO Auto-generated destructor stub
	BrickTex = NULL;
}

