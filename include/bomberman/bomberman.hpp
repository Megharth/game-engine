/*
 * bomberman.hpp
 *
 *  Created on: Apr 2, 2020
 *      Author: saite
 */

#ifndef SRC_FINAL_BOMBERMAN_HPP_
#define SRC_FINAL_BOMBERMAN_HPP_

#include "base/ResourceManager.hpp"
#include "base/Level.hpp"
#include "base/Score.hpp"

#include <iostream>
#include <sstream>

class bomberman {
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
    int targetTime{0};
public:
	bomberman(int w, int h);
	virtual ~bomberman();
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
};

#endif /* SRC_FINAL_BOMBERMAN_HPP_ */
