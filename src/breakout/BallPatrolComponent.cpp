#include "breakout/BallPatrolComponent.hpp"
#include "base/PhysicsManager.hpp"
#include "base/SoundManager.hpp"

BallPatrolComponent::BallPatrolComponent(GameObject & gameObject, float speed):
    GenericComponent(gameObject), mSpeed(speed), pc(gameObject.physicsComponent()) {}

void BallPatrolComponent::update(Level & level) {
    std::vector<std::shared_ptr<GameObject>> objects;
    if(PhysicsManager::getInstance().getCollisions(getGameObject().x(), 
        getGameObject().y(), getGameObject().w(), getGameObject().h(), objects)) {
            for(auto obj : objects) {
                if(obj->tag() == 1) {
                    SoundManager::getInstance().playSound(2);
                    collision = true;
                }
                if(obj->tag() == 3) {
                    collision = true;
                    SoundManager::getInstance().playSound(3);
                    level.removeObject(obj);
                    level.incrementScore(10);
                }
            }
    } else { collision = false; }

    if(getGameObject().x() < 0)
        left = false;

    if(getGameObject().x() + getGameObject().w() > level.w())
        left = true;

    if(getGameObject().y() + getGameObject().h() < 35)
        up = false;

    if((getGameObject().y() + getGameObject().h()) > level.h()) {
        level.decrementLife();
        SoundManager::getInstance().playSound(4);

        getGameObject().setX((level.w()/2));
        getGameObject().setY((level.h()/2));
        pc->setPosition();
        up = !up;
        left = !left;
    } else {
        if(collision) {
            up = !up;
            collision = false;
        }

        if(up) {
            pc->setVy(-mSpeed);
        } else {
            pc->setVy(mSpeed);
        }

        if(left) {
            pc->setVx(-mSpeed);
        } else {
            pc->setVx(mSpeed);
        }
    }
}