#ifndef GOAL_COLLIDE_COMPONENT
#define GOAL_COLLIDE_COMPONENT

#include "SDL.h"
#include "base/GenericComponent.hpp"
#include "base/TextComponent.hpp"

//! \brief A component that removes a game object (of a given tag) on collision.
class GoalCollide : public GenericComponent {
public:

  GoalCollide(GameObject & gameObject, int tag, SDL_Renderer*);
  /**
   * checks the collision between the goal and the player
   * If collides then level stops and prints that you win
   */
  virtual void collision(Level & level, std::shared_ptr<GameObject> obj) override;

private:

  int mTag;
  SDL_Renderer* mRenderer;
  
};

#endif
