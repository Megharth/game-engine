#include "platformer/GoalCollide.hpp"
#include "base/Level.hpp"
#include "iostream"
#include "base/InputManager.hpp"
#include "base/SoundManager.hpp"
GoalCollide::GoalCollide(GameObject & gameObject, int tag, SDL_Renderer* renderer):
  GenericComponent(gameObject),
  mTag(tag),
  mRenderer(renderer)
{
}

void
GoalCollide::collision(Level & level, std::shared_ptr<GameObject> obj)
{
  if (obj->tag() == mTag) {
    SDL_Color color = {255, 255, 255, 0};
      level.addObject(std::make_shared<TextComponent>(level, "You win!", color, 24, 
        getGameObject().x() + 10, getGameObject().y() - 50, 
        0, 0, mRenderer));

    SoundManager::getInstance().playSound(5);
    level.setComplete(true);
    InputManager::getInstance().setBlock(true);
  }
}
