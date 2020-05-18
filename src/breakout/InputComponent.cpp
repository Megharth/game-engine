#include "breakout/InputComponent.hpp"
#include "base/SoundManager.hpp"
#include "iostream"

using namespace std;
BreakoutInputComponent::BreakoutInputComponent(GameObject & gameObject, float speed):
    GenericComponent(gameObject), mSpeed(speed) {}

void BreakoutInputComponent::update(Level &level) {

    left = InputManager::getInstance().isKeyDown(SDLK_LEFT);
    right = InputManager::getInstance().isKeyDown(SDLK_RIGHT);

    int move_action = 1;
    
    GameObject & gameObject = getGameObject();
    std::shared_ptr<PhysicsComponent> pc = gameObject.physicsComponent();

    pc->addFy(0);
    if(level.isPaused() || level.levelComplete()) {
      InputManager::getInstance().setBlock(true);
    } else {
      InputManager::getInstance().setBlock(false);
    }

    if(!InputManager::getInstance().isBlocked()) {
      if(left && !right && gameObject.x() > 10) {
          pc->setVx(-mSpeed);
          SoundManager::getInstance().playSound(move_action);
      }
      else if(!left && right && (gameObject.x() + gameObject.w() < 1280)) {
          pc->setVx(mSpeed);
          SoundManager::getInstance().playSound(move_action);
      }
      else
          pc->setVx(0.0f);
    }
    
}
