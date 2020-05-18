#include "base/PatrolComponent.hpp"
#include "base/GameObject.hpp"
#include "base/PhysicsManager.hpp"

#include <cmath>
#include "iostream"


PatrolComponent::PatrolComponent(GameObject & gameObject, float dx, float dy, float speed):
  GenericComponent(gameObject), mSpeed(speed), ox(gameObject.x()), oy(gameObject.y()), 
  pc(gameObject.physicsComponent()), dx(dx), dy(dy)
{
	right = true;
	toX = ox + dx;
	
	// pc->addFy(1000000.0f);
}

void
PatrolComponent::update(Level & level)
{
	std::vector<std::shared_ptr<GameObject>> objects;
	if(PhysicsManager::getInstance().getCollisions(getGameObject().x(), 
		getGameObject().y(), getGameObject().w(), getGameObject().h() - 10, objects)) {
			for(auto obj : objects) {
				if(obj->tag() == 4 || obj->tag() == 3)
					collision = true;
			}
	} else { collision = false; }
	if(abs(getGameObject().x() - toX) <= 1 || collision) 
	{
		collision = false;
		right = !right;
		if(toX < ox) {
			toX = ox + dx;
			if(toX >= 1280)
				toX = 1000;
		} else {
			toX = ox - dx;
			if(toX <= 0)
				toX = 10;
		}
	}
	getGameObject().setRun(true);
	if(right) {
		pc->setVx(mSpeed);
		getGameObject().setRight(true);
		getGameObject().setLeft(false);
	} else {
		pc->setVx(-mSpeed);
		getGameObject().setRight(false);
		getGameObject().setLeft(true);
	}
}

bool PatrolComponent::getright()
{
	return right;
}
