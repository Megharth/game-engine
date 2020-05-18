#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include "ResourceManager.hpp"
//! managing the sound
class SoundManager {
private:
    SoundManager() = default;
    SoundManager(SoundManager const&) = delete;
    void operator=(SoundManager const&) = delete;
    int channel{0};
    Mix_Chunk 
        *move = NULL, 
        *jump = NULL,
        *win = NULL,
        *collect = NULL,
        *death = NULL;
    int 
        move_action = 1,
        jump_action = 2,
        collect_action = 3,
        player_death = 4,
        win_action = 5;

    std::string program;



public:

    static SoundManager &getInstance();

    void startUp(std::string);
    void shutDown();

    void playSound(int action);
};

#endif
