/**
 * Platformer.cpp
 * Author: Megharth
 */

// IMP: USE 4 SPACES FOR TAB!

#include "platformer/Platformer.hpp"
#include "platformer/Character.hpp"
#include "platformer/Blocks.hpp"
#include "platformer/Goal.hpp"
#include "base/InputManager.hpp"
#include "base/Level.hpp"
#include "base/PhysicsManager.hpp"
#include "platformer/collectible.hpp"
#include "base/SoundManager.hpp"
#include "platformer/spring.hpp"
#include "platformer/Enemy.hpp"
#include "platformer/Boost.hpp"
#include "platformer/BoostLeft.hpp"
#include "base/TextureManager.hpp"

#include "base/Score.hpp"
#include "base/GameObject.hpp"

// DO NOT WRITE CUSTOM CLASSES BELOW THIS.

#include <string.h>
#include <chrono>
#include <memory>

int Platformer::load_level(SDL_Renderer* gRenderer) {
    std::string* levelDetails = ResourceManager::getInstance().load_level("platformer/level" + std::to_string(currentLevel));
    for(int i=0; i<20; i++) {
        for(int j=0; j<20; j++) {
            if(levelDetails[i][j] == 'F') {
                level->addObject(std::make_shared<Goal>(*level, "platformer/pointer.png", j*64, (i*36) - 92, gRenderer));
            }
            if(levelDetails[i][j] == 'P')
                level->addObject(std::make_shared<Character>(*level, "platformer/character", j*64, (i*36) - 25, gRenderer));
            if(levelDetails[i][j] == 'B') {
                level->addObject(std::make_shared<Block>(*level, "platformer/box.png", j*64, i*36, gRenderer));
            }
            if(levelDetails[i][j] == 'G') {
                level->addObject(std::make_shared<Block>(*level, "platformer/ground-flat.png", j*64, i*36, gRenderer));
            }
            if(levelDetails[i][j] == 'C') {
                level->addObject(std::make_shared<Block>(*level, "platformer/crust.png", j*64, i*36, gRenderer));
            }
            if(levelDetails[i][j] == 'S'){
            	level->addObject(std::make_shared<collectible>(*level, "platformer/coin.png", j*64, i*36, gRenderer));
            }
            if(levelDetails[i][j] == 'R'){
                level->addObject(std::make_shared<spring>(*level, "platformer/spring.png", j*64, i*36, gRenderer));
            }
            if(levelDetails[i][j] == 'E'){
                level->addObject(std::make_shared<Enemy>(*level, "platformer/enemy", j*64, (i*36) - 25, gRenderer));
            }
            if(levelDetails[i][j] == 'W'){
                level->addObject(std::make_shared<Boost>(*level, "platformer/boost.png", j*64, i*36, gRenderer));
            }
            if(levelDetails[i][j] == 'L'){
                level->addObject(std::make_shared<BoostLeft>(*level, "platformer/boostleft.png", j*64, i*36, gRenderer));
            }
        }
    }
    return 0;
}

Platformer::Platformer(int w, int h):screenHeight(h), screenWidth(w) {
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
        bgMusic = ResourceManager::getInstance().load_track("platformer/background.mp3");
        if(bgMusic == NULL) {
            std::cout<<"Error background sound"<<Mix_GetError()<<std::endl;
        	success = false;
        }

        Mix_PlayMusic(bgMusic, -1);
        PhysicsManager::getInstance().startUp();
        SoundManager::getInstance().startUp("platformer");
        level = std::make_shared<Level>(screenWidth, screenHeight);
        load_level(gRenderer);
        InputManager::getInstance().startUp();

        score.init();
    }


    if(!success){
        errorStream << "Failed to initialize!\n";
        std::string errors=errorStream.str();
        std::cout << errors << "\n";
    }else{
        std::cout << "No SDL errors Detected in during init\n\n";
    }
}

Platformer::~Platformer() {
    PhysicsManager::getInstance().shutDown();
    ResourceManager::getInstance().shutDown();
    InputManager::getInstance().shutDown();
    SoundManager::getInstance().shutDown();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(window);
    gRenderer = NULL;
    window = NULL;

    // CLOSE AND CLEANUP EVERYTHING BEFORE THIS
    SDL_Quit();
}

void Platformer::update(float time) {
    if(level->started() && 
        !level->isPaused() &&
        !level->getdeath() &&
        currentLevel <= 3
        ) {
        level->update();
        for(int i=0;i<level->getscorecount();i++)
        {
            score.incrementScore(1);
        }
    }

    if(reload && level->getdeath()) {
        level->setdeath(false);
        level->finalize();
        load_level(gRenderer);
        score.init();
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

void Platformer::render() {
    SDL_SetRenderDrawColor(gRenderer, 0x22,0x22,0x22,0xFF);
    SDL_RenderClear(gRenderer);

    int w, h;
    SDL_Texture* bgImage = ResourceManager::getInstance().load_texture("platformer/background.png", gRenderer);
    SDL_QueryTexture(bgImage,NULL, NULL, &w, &h);
    TextureManager::getInstance().renderTexture(bgImage, gRenderer, (screenWidth/2)-(w/2), (screenHeight/2)-(h/2)); 
    SDL_Color color = { 44, 150, 200, 0};
    SDL_Texture *coin = ResourceManager::getInstance().load_texture("platformer/coin.png", gRenderer);
    TextureManager::getInstance().renderTexture(coin, gRenderer, screenWidth-120, 18, 46, 46);

    SDL_Texture *points_count = TextureManager::getInstance().renderText("x" + std::to_string(score.getScore()), "fonts/Asar-Regular.ttf", 0, color, 32, gRenderer);
    TextureManager::getInstance().renderTexture(points_count, gRenderer, screenWidth-60, 12);

    if(level->isPaused()) {
        color = {255, 255, 155, 255};
        SDL_Texture *points_count = TextureManager::getInstance().renderText("PAUSED", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
        TextureManager::getInstance().renderTexture(points_count, gRenderer, 500, 600);
    }

    level->render(gRenderer);

    if(!level->started()) {
        color = {255, 255, 155, 255};
        SDL_Texture *start_text = TextureManager::getInstance().renderText("PRESS ENTER", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
        TextureManager::getInstance().renderTexture(start_text, gRenderer, 400, 100);
        start_text = TextureManager::getInstance().renderText("TO START THE GAME", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
        TextureManager::getInstance().renderTexture(start_text, gRenderer, 300, 150);

        start_text = TextureManager::getInstance().renderText("Controls", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
        TextureManager::getInstance().renderTexture(start_text, gRenderer, 480, 350);

        start_text = TextureManager::getInstance().renderText("Use Arrow Keys", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
        TextureManager::getInstance().renderTexture(start_text, gRenderer, 350, 400);

        start_text = TextureManager::getInstance().renderText("Press ESC to", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
        TextureManager::getInstance().renderTexture(start_text, gRenderer, 400, 470);

        start_text = TextureManager::getInstance().renderText("Pause the game!", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
        TextureManager::getInstance().renderTexture(start_text, gRenderer, 350, 520);
    }

    if(level->getdeath()) {
        SDL_Texture *death = TextureManager::getInstance().renderText("YOU DIED!", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
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
        color = {255, 255, 155, 255};
        SDL_Texture* win_text = TextureManager::getInstance().renderText("You win!", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
        TextureManager::getInstance().renderTexture(win_text, gRenderer, 550, 300);

        win_text = TextureManager::getInstance().renderText("Game Over!", "fonts/ghostclan.ttf", 0, color, 64, gRenderer);
        TextureManager::getInstance().renderTexture(win_text, gRenderer, 500, 400);
    }    

    SDL_RenderPresent(gRenderer);
}

void Platformer::loop() {
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

SDL_Window* Platformer::getWindow() {
    return window;
}

SDL_Renderer* Platformer::getRenderer() {
    return gRenderer;
}
