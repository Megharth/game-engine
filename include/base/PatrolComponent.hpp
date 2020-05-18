#ifndef BASE_PATROL_COMPONENT
#define BASE_PATROL_COMPONENT

#include "base/GenericComponent.hpp"
#include "base/PhysicsComponent.hpp"

//! \brief A component that causes its game object to patrol back and forth.
class PatrolComponent: public GenericComponent {
public:

  PatrolComponent(GameObject & gameObject, float toX, float toY, float speed);
  
  virtual void update(Level & level);

  bool getright();

private:

  bool right;
  float dx;
  float dy;
  float toX;
  float toY;
  float ox;
  float oy;
  float mSpeed;
  bool collision{false};
  std::shared_ptr<PhysicsComponent> pc;


};

#endif
