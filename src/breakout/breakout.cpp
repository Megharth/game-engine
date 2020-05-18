#include "breakout/breakout.hpp"
#include "breakout/Paddle.hpp"
#include "breakout/Ball.hpp"

#include "base/Brick.hpp"
#include "base/InputManager.hpp"
#include "base/TextureManager.hpp"
#include "base/PhysicsManager.hpp"
#include "base/SoundManager.hpp"

#include <string.h>
#include <chrono>
#include <memory>

int breakout::load_level(SDL_Renderer* gRenderer) {
	std::string* levelDetails = ResourceManager::getInstance().load_level("breakout/level" + std::to_string(currentLevel));
	for(int i=0; i<20; i++) {
		for(int j=0; j<20; j++) {
			if(levelDetails[i][j] == 'Z') {
				level->addObject(std::make_shared<Brick>(*level, "breakout/brick.png", false, j*64, i*36, 100, 30, 0, gRenderer));
				targetScore += 10;
			}
		}
	}
	if(!reload) {
		level->addObject(std::make_shared<Paddle>(*level, "breakout/paddle.png", (screenWidth / 2) - 100, screenHeight - 70, gRenderer));
		level->addObject(std::make_shared<Ball>(*level, "breakout/ball.png", (screenWidth / 2) - 25, (screenHeight / 2) - 25, gRenderer));
	}
	return 0;
}

breakout::breakout(int w,int h):screenHeight(h), screenWidth(w){
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

	        ResourceManager::getInstance().startUp();

			bgMusic = ResourceManager::getInstance().load_track("breakout/background.mp3");
			if(bgMusic == NULL) {
				std::cout<<"Error background sound"<<Mix_GetError()<<std::endl;
				success = false;
			}

			Mix_PlayMusic(bgMusic, -1);

	    	PhysicsManager::getInstance().startUp();
			SoundManager::getInstance().startUp("breakout");
			level = std::make_shared<Level>(screenWidth, screenHeight);
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

breakout::~breakout(){
	ResourceManager::getInstance().shutDown();
	PhysicsManager::getInstance().shutDown();
	InputManager::getInstance().startUp();
	SoundManager::getInstance().shutDown();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window);
	gRenderer = NULL;
	window = NULL;

	SDL_Quit();
}

void breakout::update(float time) {

	if(level->getScore() >= targetScore && currentLevel <= 3) {
		level->setComplete(true);
		SoundManager::getInstance().playSound(5);
	}

	if(level->getLives() <= 0) {
		level->setdeath(true);
	}
	if(level->started() &&
		!level->isPaused() &&
		!level->getdeath() &&
		!level->levelComplete() &&
		currentLevel <= 3)
		level->update();

	if(reload && level->getdeath()) {
		level->setdeath(false);
		targetScore = 0;
		load_level(gRenderer);
		level->resetScore();
		level->setLife(3);
		reload = false;
	}

	if(level->levelComplete()) {
		if(nextLevel) {
			level->finalize();
			currentLevel++;
			load_level(gRenderer);
			level->setComplete(false);
			nextLevel = false;
		}
	}
}

void breakout::render() {
	SDL_SetRenderDrawColor(gRenderer, 0x22,0x22,0x22,0xFF);
	SDL_RenderClear(gRenderer);

	SDL_Color color = { 255, 255, 255, 0};
	SDL_Texture *points_count = TextureManager::getInstance().renderText("Score : " + std::to_string(level->getScore()), "fonts/Asar-Regular.ttf", 0, color, 32, gRenderer);
	TextureManager::getInstance().renderTexture(points_count, gRenderer, screenWidth-200, 12);

	SDL_Texture *lives = TextureManager::getInstance().renderText("Lives : " + std::to_string(level->getLives()), "fonts/Asar-Regular.ttf", 0, color, 32, gRenderer);
	TextureManager::getInstance().renderTexture(lives, gRenderer, 50, 12);

	if(level->isPaused()) {
		SDL_Texture* paused = ResourceManager::getInstance().load_texture("breakout/paused-text.png", gRenderer);
		TextureManager::getInstance().renderTexture(paused, gRenderer, (screenWidth/2)-100, (screenHeight/2)-25);
	}

	level->render(gRenderer);

	if(!level->started()) {
		SDL_Texture* start = ResourceManager::getInstance().load_texture("breakout/start-text.png", gRenderer);
		TextureManager::getInstance().renderTexture(start, gRenderer, (screenWidth/2) - 250, (screenHeight/2)-50);
	}

	if(level->getdeath()) {
		SDL_Texture* lose = ResourceManager::getInstance().load_texture("breakout/death-text.png", gRenderer);
		TextureManager::getInstance().renderTexture(lose, gRenderer, (screenWidth/2)-20, (screenHeight/2));

		SDL_Texture* reload = ResourceManager::getInstance().load_texture("breakout/reload-text.png", gRenderer);
		TextureManager::getInstance().renderTexture(reload, gRenderer, (screenWidth/2)-150, (screenHeight/2)+50);
	}

	if(level->levelComplete()) {
		SDL_Texture* next = ResourceManager::getInstance().load_texture("breakout/next-level-text.png", gRenderer);
		TextureManager::getInstance().renderTexture(next, gRenderer, (screenWidth/2)-250, (screenHeight/2)-50);
	}

	if(currentLevel > 3) {
		SoundManager::getInstance().playSound(5);
		SDL_Texture* win = ResourceManager::getInstance().load_texture("breakout/win-text.png", gRenderer);
		TextureManager::getInstance().renderTexture(win, gRenderer, (screenWidth/2)-200, (screenHeight/2)-50);
	}
	SDL_RenderPresent(gRenderer);

}

void breakout::loop() {
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
				if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
					level->setPaused(!level->isPaused());
				}
				if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN && !level->started()) {
					level->setStart(true);
				} 
				if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {
					reload = true;
				}
				if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n) {
					nextLevel = true;
				}
				if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b) {
					level->incrementScore(10);
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
	        }
	    }
		level->finalize();
	    SDL_StopTextInput();

}


SDL_Window* breakout::getWindow() {
    return window;
}

SDL_Renderer* breakout::getRenderer() {
    return gRenderer;
}
