#include "base/SoundManager.hpp"
#include "base/ResourceManager.hpp"
#include "iostream"

SoundManager&
SoundManager::getInstance() {
    static SoundManager * instance = new SoundManager();
    return *instance;
}

void SoundManager::startUp(std::string program_name) {
    program = program_name;
    if(strcmp("platformer", program.c_str()) == 0) {
        move = ResourceManager::getInstance().load_music(program + "/walk.mp3");
        if(move == NULL) {
            std::cout<<"Error walk sound"<<Mix_GetError()<<std::endl;
        }
        
        jump = ResourceManager::getInstance().load_music(program + "/jump.mp3");
        if(jump == NULL) {
            std::cout<<"Error Jump sound"<<Mix_GetError()<<std::endl;
        }
        collect = ResourceManager::getInstance().load_music(program + "/coinsound.mp3");
        if(collect == NULL) {
            std::cout<<"Error coin collect sound"<<Mix_GetError()<<std::endl;
        }
        death = ResourceManager::getInstance().load_music(program + "/playerdeath.mp3");
        if(death == NULL) {
            std::cout<<"Error player death sound"<<Mix_GetError()<<std::endl;
        }

        win = ResourceManager::getInstance().load_music(program + "/win.mp3");
        if(win == NULL) {
            std::cout<<"Error win sound"<<Mix_GetError()<<std::endl;
        }
    } else if(strcmp("breakout", program.c_str()) == 0) {
        jump = ResourceManager::getInstance().load_music(program + "/paddle.mp3");
        if(jump == NULL) {
            std::cout<<"Error paddle sound"<<Mix_GetError()<<std::endl;
        }

        win = ResourceManager::getInstance().load_music(program + "/win.mp3");
        if(win == NULL) {
            std::cout<<"Error win sound"<<Mix_GetError()<<std::endl;
        }

        collect = ResourceManager::getInstance().load_music(program + "/collide.mp3");
        if(collect == NULL) {
            std::cout<<"Error coin collect sound"<<Mix_GetError()<<std::endl;
        }

        death = ResourceManager::getInstance().load_music(program + "/death.mp3");
        if(death == NULL) {
            std::cout<<"Error player death sound"<<Mix_GetError()<<std::endl;
        }
    } else if(strcmp("bomberman", program.c_str()) == 0) {
        move = ResourceManager::getInstance().load_music(program + "/drop.mp3");
        if(move == NULL) {
            std::cout<<"Error walk sound"<<Mix_GetError()<<std::endl;
        }

        jump = ResourceManager::getInstance().load_music(program + "/Explosion.mp3");
        if(jump == NULL) {
            std::cout<<"Error explosion sound"<<Mix_GetError()<<std::endl;
        }

        win = ResourceManager::getInstance().load_music(program + "/win.mp3");
        if(win == NULL) {
            std::cout<<"Error win sound"<<Mix_GetError()<<std::endl;
        }

        collect = ResourceManager::getInstance().load_music(program + "/collect.mp3");
        if(collect == NULL) {
            std::cout<<"Error coin collect sound"<<Mix_GetError()<<std::endl;
        }

        death = ResourceManager::getInstance().load_music(program + "/death.mp3");
        if(death == NULL) {
            std::cout<<"Error player death sound"<<Mix_GetError()<<std::endl;
        }
    }
}

void SoundManager::shutDown() {
    move = NULL;
    jump = NULL;
    collect = NULL;
    death = NULL;
    win = NULL;
}

void SoundManager::playSound(int action) {
    if(action == move_action && Mix_Playing(channel) == 0) {
        channel = Mix_PlayChannel(-1, move, 0);
    }

    if(action == jump_action && Mix_Playing(1) == 0) {
        channel = Mix_PlayChannel(1, jump, 0);
    }

    if(action == collect_action && Mix_Playing(2) == 0){
    	channel = Mix_PlayChannel(2, collect, 0);
    }

    if(action == player_death && Mix_Playing(3) == 0){
       channel = Mix_PlayChannel(3, death, 0);
    }

    if(action == win_action && Mix_Playing(4) == 0) {
        channel = Mix_PlayChannel(4, win, 0);
    }
}
