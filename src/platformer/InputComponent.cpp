#include "platformer/InputComponent.hpp"
#include "base/PhysicsManager.hpp"
#include "base/SoundManager.hpp"
#include "iostream"

using namespace std;
InputComponent::InputComponent(GameObject & gameObject, float speed, float jump, float gravity):
    GenericComponent(gameObject), mSpeed(speed), mJump(jump), mGravity(gravity) {}

void InputComponent::update(Level &level) {

    left = InputManager::getInstance().isKeyDown(SDLK_LEFT);
    right = InputManager::getInstance().isKeyDown(SDLK_RIGHT);
    jump = InputManager::getInstance().isKeyDown(SDLK_UP);

    int walk_action = 1;
    int jump_action = 2;
    int coin_collect = 3;
    
    GameObject & gameObject = getGameObject();
    std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();
    
    pc->addFy(mGravity);

    if(level.isPaused() || level.levelComplete()) {
      InputManager::getInstance().setBlock(true);
    } else {
      InputManager::getInstance().setBlock(false);
    }

    if(!InputManager::getInstance().isBlocked()) {
      if(left && !right) {
          pc->setVx(-mSpeed);
          SoundManager::getInstance().playSound(walk_action);
      }
      else if(!left && right) {
          pc->setVx(mSpeed);
          SoundManager::getInstance().playSound(walk_action);
      }
      else
          pc->setVx(0.0f);

      if (jump) {
        bool onGround = false;
        SoundManager::getInstance().playSound(jump_action);

        std::vector<std::shared_ptr<GameObject>> objects;
        if (PhysicsManager::getInstance().getCollisions(gameObject.x() + 1, gameObject.y() + gameObject.h(), gameObject.w() - 2, 2.0f, objects)) {
          for (auto obj: objects) {
            if (obj->tag() == 9) {
              onGround = true;
            }
          }
        }
        if (onGround) {
          pc->setVy(-mJump);
        }
      }
      std::vector<std::shared_ptr<GameObject>> objects;
      if (PhysicsManager::getInstance().getCollisions(gameObject.x(), gameObject.y() , gameObject.w(),  gameObject.h(), objects)) {
        for (auto obj: objects) {
          if(obj->tag() == 7) {
            pc->addFy(-500000000.0f);
          }
        }
        }
      if (PhysicsManager::getInstance().getCollisions(gameObject.x(), gameObject.y() , gameObject.w(),  gameObject.h(), objects))
      {
    	  for (auto obj: objects)
    	  {
        	 if(obj->tag() == 8)
        	 {
        		 pc->addFx(1000000000000000000000000.0f);
             }
        	 else if (obj->tag() == 10)
        	 {
        		 pc->addFx(-1000000000000000000000000.0f);
        	 }
    	  }
      }
    }
    
}
