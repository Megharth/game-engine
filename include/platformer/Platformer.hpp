/**
 * Platformer.hpp
 * Author: Megharth
 */

#ifndef PLATFORMER_HPP
#define PLATFORMER_HPP

#include "base/ResourceManager.hpp"
#include "base/Level.hpp"
#include "base/Score.hpp"


#include <iostream>
#include <sstream>

//! \brief It contains the main code of the platformer game
//! It contains the frame update method, render method and main loop that runs the game.
class Platformer {
private:
    int screenHeight;
    int screenWidth;
    SDL_Window* window;
    SDL_Renderer* gRenderer = NULL;
    Mix_Music* bgMusic = NULL;
    const int FPS = 60;
    int currentLevel{1};
    bool reload{false};
    bool nextLevel{false};
public:
    /**
     * constructor where all the intialization for the game happen
     */
    Platformer(int w, int h);

    ~Platformer();

    /**
     * update the whole objects on the screen after every frame
     */
    void update(float);

    /**
     * render everything that should be on screen
     */
    void render();

    /**
     * main loop where the game starts
     */
    void loop();

    /**
     * returns the window variable which contains the window
     */
    SDL_Window* getWindow();

    /**
     * returns the render variable that gets rendered every frame
     */
    SDL_Renderer* getRenderer();

    void DisplayWin();

    int load_level(SDL_Renderer*);
    
    std::shared_ptr<Level> level;
    Score score;
};

#endif 
