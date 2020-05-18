#include "base/StatesAndTransitions.hpp"
#include "base/GameObject.hpp"
#include "base/Level.hpp"
#include <cmath>

// move the gameObject toward x,y at speed
// return true if reached
static
bool
moveToward(GameObject & gameObject, float x, float y, float speed)
{
  const float epsilon = 0.01;
  
  float dX = x - gameObject.x();
  float dY = y - gameObject.y();
  const float len = sqrtf(dX * dX + dY * dY);
  if (len < epsilon) {
    return true;
  } else {
    const float scale = std::min(len, speed);
    dX = dX / len * scale;
    dY = dY / len * scale;
  
    gameObject.setX(gameObject.x() + dX);
    gameObject.setY(gameObject.y() + dY);
  
    return (speed >= len - epsilon);
  }
}

// return true if gameobject is less than distance from x,y
static
bool
isNear(const GameObject & gameObject, float x, float y, float distance)
{
  const float dX = x - gameObject.x();
  const float dY = y - gameObject.y();
  const float lensqr = dX * dX + dY * dY;
  return lensqr <= distance * distance;
}



PatrolState::PatrolState(float speed, float x0, float y0, float x1, float y1):
  mSpeed(speed),
  mX0(x0),
  mY0(y0),
  mX1(x1),
  mY1(y1),
  mForward(true)
{
}

void
PatrolState::onEnter()
{
  mForward = true;
}

void
PatrolState::update(GameObject & gameObject, Level & level)
{
	const float tx = mForward ? mX1 : mX0 ;
	const float ty = mForward ? mY1 : mY0 ;
	if(moveToward(gameObject, tx, ty, mSpeed))
	{
		mForward = !mForward;
	}

  // TODO PART 2: implement patrolling (using moveToward)


}



ChaseState::ChaseState(float speed, std::weak_ptr<GameObject> which):
  mSpeed(speed),
  mWhich(which)
{
}

void
ChaseState::update(GameObject & gameObject, Level & level)
{
  std::shared_ptr<GameObject> whichShared = mWhich.lock();

  if (whichShared) {
    moveToward(gameObject, whichShared->x(), whichShared->y(), mSpeed);
  }
}



MoveState::MoveState(float speed, float x, float y):
  mSpeed(speed),
  mX(x),
  mY(y)
{
}

void
MoveState::update(GameObject & gameObject, Level & level)
{
  moveToward(gameObject, mX, mY, mSpeed);
}



ObjectProximityTransition::ObjectProximityTransition(std::weak_ptr<GameObject> which, float distance):
  mWhich(which),
  mDistance(distance)
{
}

bool
ObjectProximityTransition::shouldTrigger(GameObject & gameObject, Level & level)
{

  std::shared_ptr<GameObject> whichShared = mWhich.lock();

    if (whichShared) {
    	if(level.hasObject(whichShared)){
    		  return isNear(gameObject, whichShared->x(), whichShared->y(), mDistance);
    	}

    }

    return false;
   // TODO PART 3: check the level still has the game object being checked, and this gameObject is near it
}



PointProximityTransition::PointProximityTransition(float x, float y, float distance):
  mX(x),
  mY(y),
  mDistance(distance)
{
}

bool
PointProximityTransition::shouldTrigger(GameObject & gameObject, Level & level)
{
  return isNear(gameObject, mX, mY, mDistance);
}



TimedTransition::TimedTransition(int steps):
  mSteps(steps),
  mStep(0)
{
}

void
TimedTransition::onEnterState()
{
  mStep = 0;
}

bool
TimedTransition::shouldTrigger(GameObject & gameObject, Level & level)
{
  ++ mStep;
  return mStep >= mSteps;
}
