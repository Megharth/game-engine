#include "bomberman/ExplosionComponent.hpp"
#include "base/PhysicsManager.hpp"
#include "base/SoundManager.hpp"
#include "base/PhysicsComponent.hpp"
#include <iostream>

ExplosionComponent::ExplosionComponent(GameObject & gameObject, double t, bool b):GenericComponent(gameObject) {
    timeout = t;
	previous = std::chrono::system_clock::now();
	blast = b;
}

void ExplosionComponent::update(Level & level,bool b) {
	blast = b;
    current = std::chrono::system_clock::now();
    if(blast && !came){
       previous = current;
       came = true;
    }
    std::chrono::duration<double> elapsed = current - previous;
    GameObject & gameObject = getGameObject();
    if((elapsed.count() * 1000.0) >= timeout + 400.0 || (blast && (elapsed.count()*1000.0) >= 300.0)) {
        SoundManager::getInstance().playSound(2);
        std::vector<std::shared_ptr<GameObject>> objects;
        if (PhysicsManager::getInstance().getCollisions(gameObject.x() - 20, gameObject.y() - 20, gameObject.w() + 50, gameObject.h() + 50, objects)) {
          for (auto obj: objects) {
            if(obj->isStrong()) {
              obj->setStrong(false);
            } else if(obj->tag() == 5 || obj->tag() == 6) {
              obj->setCollectibleVisibility(true);
              obj->setPhysicsCompenent(std::make_shared<PhysicsComponent>(*obj, PhysicsComponent::Type::STATIC_SENSOR));
            } else if(obj->tag() == 1) {
              level.setdeath(true);
            }else {
              level.removeObject(obj);
            }
          }
        }
        level.removeObject(getGameObject().shared_from_this());
    }
}
