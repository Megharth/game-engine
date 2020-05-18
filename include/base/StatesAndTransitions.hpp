#ifndef BASE_STATES
#define BASE_STATES

#include "base/StateComponent.hpp"
#include <memory>

// ********** STATES **********

//! \brief A state to patrol back and forth
class PatrolState: public StateComponent::State {
public:

  PatrolState(float speed, float x0, float y0, float x1, float y1);
 
  virtual void onEnter() override; 
  virtual void update(GameObject & gameObject, Level & level) override;

private:

  const float mSpeed;
  const float mX0, mY0, mX1, mY1;

  bool mForward;

};

//! \brief A state to chase something
class ChaseState: public StateComponent::State {
public:

  ChaseState(float speed, std::weak_ptr<GameObject> which);
 
  virtual void update(GameObject & gameObject, Level & level) override;

private:

  const float mSpeed;
  const std::weak_ptr<GameObject> mWhich;

};

//! \brief A state to move somewhere
class MoveState: public StateComponent::State {
public:

  MoveState(float speed, float x, float y);
 
  virtual void update(GameObject & gameObject, Level & level) override;

private:

  const float mSpeed;
  const float mX, mY;

};

// ********** TRANSITIONS **********

//! \brief A transition that triggers when near another gameobject
class ObjectProximityTransition: public StateComponent::Transition {
public:

  ObjectProximityTransition(std::weak_ptr<GameObject> which, float distance);

  virtual bool shouldTrigger(GameObject & gameObject, Level & level) override;

private:

  const std::weak_ptr<GameObject> mWhich;
  const float mDistance;

};

//! \brief A transition that triggers when near a point
class PointProximityTransition: public StateComponent::Transition {
public:

  PointProximityTransition(float x, float y, float distance);

  virtual bool shouldTrigger(GameObject & gameObject, Level & level) override;

private:

  const float mX, mY;
  const float mDistance;

};

//! \brief A transition that triggers after a certain time
class TimedTransition: public StateComponent::Transition {
public:

  TimedTransition(int steps);

  virtual void onEnterState() override;
  virtual bool shouldTrigger(GameObject & gameObject, Level & level) override;

private:

  const int mSteps;
  int mStep;

};

#endif
