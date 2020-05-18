#include "bomberman/InputComponent.hpp"
#include "bomberman/Bomb.hpp"
#include "base/SoundManager.hpp"
#include "base/PhysicsManager.hpp"



BombermanInputComponent::BombermanInputComponent(GameObject & gameObject, float speed):GenericComponent(gameObject) {
    mSpeed = speed;
}

void BombermanInputComponent::update(Level & level) { 
    bool x = InputManager::getInstance().isKeyDown(SDLK_x);
    bool h = InputManager::getInstance().isKeyDown(SDLK_h);

    left = InputManager::getInstance().isKeyDown(SDLK_LEFT);
    right = InputManager::getInstance().isKeyDown(SDLK_RIGHT);
    up = InputManager::getInstance().isKeyDown(SDLK_UP);
    down = InputManager::getInstance().isKeyDown(SDLK_DOWN);
    int move_action = 1;

    bool hint = false;

    GameObject & gameObject = getGameObject();

    std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();

    pc->addFy(0);

    if(level.isPaused() || level.levelComplete()) {
      InputManager::getInstance().setBlock(true);
    } else {
      InputManager::getInstance().setBlock(false);
    }

    if(!InputManager::getInstance().isBlocked()) {
        if(left && !right && gameObject.x() > -20) {
            pc->setVx(-mSpeed);
            gameObject.setLeft(true);
            gameObject.setRight(false);
            gameObject.setUp(false);
            gameObject.setDown(false);
            gameObject.setRun(true);
        }
        else if(!left && right && (gameObject.x() + gameObject.w() < level.w() + 20)) {
            pc->setVx(mSpeed);
            gameObject.setLeft(false);
            gameObject.setRight(true);
            gameObject.setUp(false);
            gameObject.setDown(false);
            gameObject.setRun(true);
        }
        else {
            pc->setVx(0.0f);
            gameObject.setRun(false);
        }

        if(up && !down && gameObject.y() > -20) {
            pc->setVy(-mSpeed);
            gameObject.setLeft(false);
            gameObject.setRight(false);
            gameObject.setUp(true);
            gameObject.setDown(false);
            gameObject.setRun(true);
        }
        else if(down && !up && gameObject.y() + gameObject.h() < level.h() + 20) {
            pc->setVy(mSpeed);
            gameObject.setLeft(false);
            gameObject.setRight(false);
            gameObject.setUp(false);
            gameObject.setDown(true);
            gameObject.setRun(true);
        }
        else {
            pc->setVy(0);
        }

        if(x && !InputManager::getInstance().isKeyBlocked(SDLK_x)) {
            if(gameObject.left()) {
                level.addObject(std::make_shared<Bomb>(level, "bomberman/bomb.png", gameObject.x() + gameObject.w()/4, gameObject.y() + gameObject.h() / 6, level.getRenderer()));
            } else if(gameObject.right()) {
                level.addObject(std::make_shared<Bomb>(level, "bomberman/bomb.png", gameObject.x() + gameObject.w()/4, gameObject.y() + gameObject.h()/6, level.getRenderer()));
            } else if(gameObject.up()) {
                level.addObject(std::make_shared<Bomb>(level, "bomberman/bomb.png", gameObject.x() + gameObject.w()/4, gameObject.y(), level.getRenderer()));
            } else {
                level.addObject(std::make_shared<Bomb>(level, "bomberman/bomb.png", gameObject.x() + gameObject.w()/4, gameObject.y() + gameObject.h() / 6, level.getRenderer()));

            }
            InputManager::getInstance().blockKey(SDLK_x);
            SoundManager::getInstance().playSound(1);
        }



        std::vector<std::shared_ptr<GameObject>> objects;
        if(PhysicsManager::getInstance().getCollisions(gameObject.x(), gameObject.y(), gameObject.w(), gameObject.h(), objects)) {
            for(auto obj : objects) {
                if(obj->tag() == 5 && obj->isCollectibleVisible()) {
                    if((gameObject.left() 
                        || gameObject.right() 
                        || gameObject.up() 
                        || gameObject.down()) 
                        && abs(gameObject.x() - obj->x() <= 10 && gameObject.y() - obj->y() <= 10)) {
                            SoundManager::getInstance().playSound(5);
                            level.setComplete(true);
                        }

                }
                if(obj->tag() == 6 && obj->isCollectibleVisible()) {
                    if((gameObject.left() 
                        || gameObject.right() 
                        || gameObject.up() 
                        || gameObject.down()) 
                        && abs(gameObject.x() - obj->x() <= 10 && gameObject.y() - obj->y() <= 30)) {
                            level.removeObject(obj);
                            level.setLife(level.getLives() + 1); 
                            SoundManager::getInstance().playSound(3);
                        }

                }
            }
        }

        if(!hint && h) {
            hint = true;
            objects = level.getObjects();
            for(auto obj : objects) {
                if(obj->tag() == 5 || obj->tag() == 6)
                    obj->setCollectibleVisibility(true);
            }
        }

    }
}   
