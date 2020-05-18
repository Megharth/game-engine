/*
 * breakout.hpp
 *
 *  Created on: Mar 29, 2020
 *      Author: saite
 */

#ifndef INCLUDE_BREAKOUT_BREAKOUT_HPP_
#define INCLUDE_BREAKOUT_BREAKOUT_HPP_

#include "base/ResourceManager.hpp"
#include "base/Level.hpp"
#include "base/Score.hpp"

#include <iostream>
#include <sstream>
//! \brief Class where all the game code regarding the breakout game resides.
//! It contains update of every frame, render method and loading the levels
class breakout{
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
    int targetScore{0};

public:
    /**
     * constructor where all the intialization for the game happen
     */
    breakout(int w, int h);

    ~breakout();

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

    int load_level(SDL_Renderer*);
    
    std::shared_ptr<Level> level;
    Score score;

    int getscreenwidth(){return screenWidth;};
    int getscreenheight(){return screenHeight;};

};



#endif /* INCLUDE_BREAKOUT_BREAKOUT_HPP_ */
