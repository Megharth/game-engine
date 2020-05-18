#include "base/StateComponent.hpp"
#include "base/GameObject.hpp"

StateComponent::StateComponent(GameObject & gameObject):
  GenericComponent(gameObject)
{
}

void
StateComponent::setStartState(std::shared_ptr<State> state)
{
  mStartState = state;
}

void
StateComponent::addTransition(std::shared_ptr<State> stateFrom, std::shared_ptr<State> stateTo, std::shared_ptr<Transition> transition)
{
  mTransitionMap.insert(std::make_pair(stateFrom, std::make_pair(stateTo, transition)));
}

void
StateComponent::update(Level & level)
{
  // go to start state initially
  if (!mCurrentState) {
    if (!mStartState) {
      return;
    }

    makeStateCurrent(mStartState);
  }

  // update current state
  mCurrentState->update(getGameObject(), level);

  // check transitions
  auto range = mTransitionMap.equal_range(mCurrentState);
  for (auto ii = range.first; ii != range.second; ++ ii) {
    if (ii->second.second->shouldTrigger(getGameObject(), level)) {
      makeStateCurrent(ii->second.first);
      break;
    }
  }
}

void
StateComponent::makeStateCurrent(std::shared_ptr<State> state)
{
  mCurrentState = state;

  mCurrentState->onEnter();

  auto range = mTransitionMap.equal_range(mCurrentState);
  for (auto ii = range.first; ii != range.second; ++ ii) {
    ii->second.second->onEnterState();
  }
}



StateComponent::State::~State()
{
}

void
StateComponent::State::onEnter()
{
}



StateComponent::Transition::~Transition()
{
}

void
StateComponent::Transition::onEnterState()
{
}
