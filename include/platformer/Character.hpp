/**
 * Character.hpp
 * AUthor: Megharth
 */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "platformer/PlayerRenderComponent.hpp"
#include <iostream>

//! \brief the character game object
class Character : public GameObject {
private:
    std::string name;
    SDL_Texture* character_idle_left;
    SDL_Texture* character_idle_right;
    SDL_Texture* character_jump_left;
    SDL_Texture* character_jump_right;
    SDL_Texture* character_run_left;
    SDL_Texture* character_run_right;
    
public:
    /**
    * initialize all the spritesheets here. Take the name and find the relative sprite sheets
    */
    Character(Level &, std::string, int, int, SDL_Renderer*);
    

    /**
     * Destructor for the Character
     */
    ~Character();

};

#endif
