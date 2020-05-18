#ifndef BASE_STATE_COMPONENT
#define BASE_STATE_COMPONENT

#include "base/GenericComponent.hpp"
#include <map>
#include <memory>
#include <vector>

//class StateMachine()
//{
//	void setStartState(std::shared_ptr<State> state);
//	void addTransition(std::shared_ptr<State> stateFrom, std::shared_ptr<State> stateTo, std::shared_ptr<Transition> transition);

//}




//! \brief A component that uses states to determine its behavior.
class StateComponent: public GenericComponent {
public:

  //! \behavior A state in the state machine.
  class State {
  public:
    virtual ~State() = 0;
    virtual void onEnter(); //!< called when entering state
    virtual void update(GameObject & gameObject, Level & level) = 0; //!< called to update when this is the current state
  };
  
  //! \behavior A transition in the state machine.
  class Transition {
  public:
    virtual ~Transition() = 0;
    virtual void onEnterState(); //!< called when entering state
    virtual bool shouldTrigger(GameObject & gameObject, Level & level) = 0; //!< called to check if this transition should be followed
  };
  
  StateComponent(GameObject & gameObject);

  void setStartState(std::shared_ptr<State> state);
  void addTransition(std::shared_ptr<State> stateFrom, std::shared_ptr<State> stateTo, std::shared_ptr<Transition> transition);
  
  virtual void update(Level & level) override;

private:

  void makeStateCurrent(std::shared_ptr<State> state); //!< transtion to the given state
  
  std::shared_ptr<State> mCurrentState; //!< the current state
  std::shared_ptr<State> mStartState; //!< the start state

  std::multimap<std::shared_ptr<State>, std::pair<std::shared_ptr<State>, std::shared_ptr<Transition>>> mTransitionMap; //!< a map from states to their outgoing transitions and their destination state

};

#endif
