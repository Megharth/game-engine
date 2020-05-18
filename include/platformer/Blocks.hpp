/*
 * Blocks.hpp
 *
 *  Created on: Feb 26, 2020
 *      Author: trive
 */

#ifndef BLOCKS_HPP_
#define BLOCKS_HPP_

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include <base/BlockRenderComponent.hpp>
//! \brief renders the blocks of images.
class Block : public GameObject
{
public:

	Block(Level &, std::string, int, int, SDL_Renderer*);
	~Block();

private:
	SDL_Texture* BlockTex;


};



#endif
