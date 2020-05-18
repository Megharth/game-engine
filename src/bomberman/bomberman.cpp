/*
 * bomberman.cpp
 *
 *  Created on: Apr 2, 2020
 *      Author: saite
 */

#include "bomberman/bomberman.hpp"
#include "bomberman/Player.hpp"
#include "bomberman/Enemy.hpp"
#include "bomberman/Bomb.hpp"
#include "bomberman/Goal.hpp"
#include "bomberman/Health.hpp"
#include "bomberman/ChaseEnemy.hpp"

#include "base/InputManager.hpp"
#include "base/TextureManager.hpp"
#include "base/PhysicsManager.hpp"
#include "base/SoundManager.hpp"
#include "base/Brick.hpp"


#include <string.h>
#include <chrono>
#include <memory>

using namespace std;

bool blast = false;

int bomberman::load_level(SDL_Renderer* gRenderer) {
	std::string* levelDetails = ResourceManager::getInstance().load_level("bomberman/level" + std::to_string(currentLevel));
	level->setRenderer(gRenderer);
	std::shared_ptr<Player> player;
	for(int i=0; i<20; i++) {
		for(int j=0; j<20; j++) {
			if(levelDetails[i][j] == 'Z') {
				level->addObject(std::make_shared<Brick>(*level, "bomberman/brick.png", false, j*64, i*36, 64, 36, 1, gRenderer));
			}
			if(levelDetails[i][j] == 'P') {
				player = std::make_shared<Player>(*level, "bomberman/character", j*64, i*36, gRenderer);
				level->addObject(player);
			}
			if(levelDetails[i][j] == 'E') {
				level->addObject(std::make_shared<BombermanEnemy>(*level, "bomberman/enemy", j*64, i*36, gRenderer));
			}
			if(levelDetails[i][j] == 'S') {
				level->addObject(std::make_shared<Brick>(*level, "bomberman/brick-solid.png", true, j*64, i*36, 64, 36, 1, gRenderer));
			}
			if(levelDetails[i][j] == 'G') {
				level->addObject(std::make_shared<BombermanGoal>(*level, "bomberman/brick.png", j*64, i*36, gRenderer));
			}
			if(levelDetails[i][j] == 'H') {
				level->addObject(std::make_shared<BombermanHealth>(*level, "bomberman/brick.png", j*64, i*36, gRenderer));
			}


		}
	}
	return 0;
}

bomberman::bomberman(int w,int h):screenHeight(h), screenWidth(w) {
	srand(time(NULL));

		    bool success = true;
		    std::stringstream errorStream;
		    window = NULL;

		    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		        errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		        success = false;
		    }
		    if(TTF_Init() != 0) {
		        errorStream << "TTF Fonts could not be initialized, Error: " << SDL_GetError() << "\n";
		        success = false;
		    }

		    int imgFlags = IMG_INIT_PNG;
		    if(!(IMG_Init(imgFlags) & imgFlags)) {
		        errorStream << "SDL Image could not be initialized, Error: " << SDL_GetError() << "\n";
		        success = false;
		    }
		    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		    {
		        errorStream << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError() << std::endl;
		        success = false;
		    }
		    else {
		        window = SDL_CreateWindow("Platformer", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		        if( window == NULL ){
		            errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
		            success = false;
		        }

		        gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		        if( gRenderer == NULL ){
		            errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
		            success = false;
		        }

		    	PhysicsManager::getInstance().startUp();
		        ResourceManager::getInstance().startUp();
				SoundManager::getInstance().startUp("bomberman");

				bgMusic = ResourceManager::getInstance().load_track("bomberman/background.mp3");
				if(bgMusic == NULL) {
					std::cout<<"Error background sound"<<Mix_GetError()<<std::endl;
					success = false;
				}

				Mix_PlayMusic(bgMusic, -1);
				level = std::make_shared<Level>(screenWidth, screenHeight);
				level->setLife(3);
				load_level(gRenderer);
			    InputManager::getInstance().startUp();

		    }
		    if(!success){
		            errorStream << "Failed to initialize!\n";
		            std::string errors=errorStream.str();
		            std::cout << errors << "\n";
			}else{
		            std::cout << "No SDL errors Detected in during init\n\n";
			}
}

void bomberman::update(float time) {
	if(level->started() &&
		!level->isPaused() &&
		level->getLives() > 0 &&
		!level->levelComplete() &&
		currentLevel <= 3)
 		level->update();



    blast = level->getblast();

	if(level->getdeath()) {
		level->setdeath(false);
		level->setLife(level->getLives() - 1);
	}

	if(reload) {
	        level->setdeath(false);
	        level->finalize();
			level->setLife(3);
	        load_level(gRenderer);
	        reload = false;
	    }

	if(level->levelComplete()){
		if(nextLevel)
		{
			level->finalize();
			currentLevel++;
			load_level(gRenderer);
			level->setComplete(false);
			nextLevel = false;
		}
	}
}

void bomberman::render() {
	SDL_SetRenderDrawColor(gRenderer, 0x22,0x22,0x22,0xFF);
	SDL_Color color = { 44, 150, 200, 0};
	SDL_RenderClear(gRenderer);
	    int w, h;
	    SDL_Texture* bgImage = ResourceManager::getInstance().load_texture("bomberman/background.png", gRenderer);
	    SDL_QueryTexture(bgImage,NULL, NULL, &w, &h);
	    TextureManager::getInstance().renderTexture(bgImage, gRenderer, (screenWidth/2)-(w/2), (screenHeight/2)-(h/2));
    level->setblast(blast);

	level->render(gRenderer);

	SDL_Texture* life = ResourceManager::getInstance().load_texture("bomberman/health.png", gRenderer);
	TextureManager::getInstance().renderTexture(life, gRenderer, screenWidth - 100, 12, 40, 25);

	color = { 255, 255, 255, 0};
	SDL_Texture* life_count = TextureManager::getInstance().renderText("x" + std::to_string(level->getLives()), "fonts/Asar-Regular.ttf", 0, color, 24, gRenderer);
	TextureManager::getInstance().renderTexture(life_count, gRenderer, screenWidth - 50, 5);

	if(!level->started()) {
		SDL_Texture* start = ResourceManager::getInstance().load_texture("bomberman/start-text.png", gRenderer);
		TextureManager::getInstance().renderTexture(start, gRenderer, (screenWidth/2) - 200, (screenHeight/2)-250);

		SDL_Texture* instructions = ResourceManager::getInstance().load_texture("bomberman/instruction-text.png", gRenderer);
		TextureManager::getInstance().renderTexture(instructions, gRenderer, (screenWidth/2) - 250, (screenHeight/2)-100);
	}

	if(level->getLives() <= 0) {
		SDL_Texture *death = TextureManager::getInstance().renderText("Game Over!", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
		TextureManager::getInstance().renderTexture(death, gRenderer, 480, 50);
		SDL_Texture *restart = TextureManager::getInstance().renderText("Press 'r' to restart", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
		TextureManager::getInstance().renderTexture(restart, gRenderer, 300, 100);
	}

	if(level->levelComplete()) {
		color = {255, 255, 155, 255};
		SDL_Texture* nxt_lvl = TextureManager::getInstance().renderText("Press 'n' to", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
		TextureManager::getInstance().renderTexture(nxt_lvl, gRenderer, 450, 450);

		nxt_lvl = TextureManager::getInstance().renderText("Go to next level", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
		TextureManager::getInstance().renderTexture(nxt_lvl, gRenderer, 350, 500);
	}

	if(currentLevel > 3) {
		SDL_Texture* winText = ResourceManager::getInstance().load_texture("bomberman/win-text.png", gRenderer);
		TextureManager::getInstance().renderTexture(winText, gRenderer, (screenWidth/2) - 200, (screenHeight/2)-250);
	}


	SDL_RenderPresent(gRenderer);
}

void bomberman::loop() {
	bool quit = false;
	    SDL_Event e;

	    SDL_StartTextInput();

	    auto previous = std::chrono::system_clock::now();
	    double lag = 0.0;

	    while(!quit) {
	        while(SDL_PollEvent(&e) != 0) {
	            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)){
	                quit = true;
	            }
				if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN && !level->started()) {
					level->setStart(true);
				}
				if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n){
					level->setComplete(true);
					nextLevel = true;
			    }
				if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r){
					// level->setdeath(true);
					reload = true;
				}
				bool b = InputManager::getInstance().isKeyDown(SDLK_b);
				if(b && !InputManager::getInstance().isKeyBlocked(SDLK_b))
				        {
				        	 level->setblast(true);
				        	 InputManager::getInstance().blockKey(SDLK_b);
				        }
	           InputManager::getInstance().handleEvent(e);
	        }

	        auto current = std::chrono::system_clock::now();
	        std::chrono::duration<double> elapsed = current - previous;
	        previous = current;
	        lag += (elapsed.count() * 1000.0);
	        while(lag >= 1000.0/FPS) {
	            update(elapsed.count());
	            render();
	            lag -= 1000.0/FPS;
	            //level->setblast(false);
	            blast = false;
	        }
	    }
		level->finalize();
	    SDL_StopTextInput();

}

SDL_Window* bomberman::getWindow() {
    return window;
}

SDL_Renderer* bomberman::getRenderer() {
    return gRenderer;
}

bomberman::~bomberman() {
	// TODO Auto-generated destructor stub
	    ResourceManager::getInstance().shutDown();
	    InputManager::getInstance().shutDown();
		PhysicsManager::getInstance().shutDown();
	    SoundManager::getInstance().shutDown();

	    SDL_DestroyRenderer(gRenderer);
	    SDL_DestroyWindow(window);
	    gRenderer = NULL;
	    window = NULL;

	    // CLOSE AND CLEANUP EVERYTHING BEFORE THIS
	    SDL_Quit();
}

