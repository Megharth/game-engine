#include "base/RemoveOnCollideComponent.hpp"
#include "base/Level.hpp"
#include "base/SoundManager.hpp"
#include "iostream"
RemoveOnCollideComponent::RemoveOnCollideComponent(GameObject & gameObject, int tag):
  GenericComponent(gameObject),
  mTag(tag)
{
  previous = std::chrono::system_clock::now();
}

void
RemoveOnCollideComponent::collision(Level & level, std::shared_ptr<GameObject> obj)
{
  if (obj->tag() == mTag) {
    if(obj->tag() == 1) {
      current = std::chrono::system_clock::now();
      std::chrono::duration<double> elapsed = current - previous;
      if((elapsed.count() * 1000.0) >= 1000.0) {
        SoundManager::getInstance().playSound(4);
        level.setdeath(true);
        previous = std::chrono::system_clock::now();
      }
    } else {
      if(obj->tag() == 6) {
        SoundManager::getInstance().playSound(3);
      }
      level.removeObject(obj);
    }
  }
}
