#ifndef BASE_PHYSICS_COMPONENT
#define BASE_PHYSICS_COMPONENT

#include "base/Component.hpp"
#include "Box2D/Box2D.h"

class Level;

//! \brief A component for handling simple physics. Has a velocity and
//! a solid property.  Solid objects prevent non-solid objects from
//! moving through them, and non-solid objects can collide with each
//! other.
class PhysicsComponent: public Component {
public:

  enum class Type {
    DYNAMIC_SOLID,
    STATIC_SOLID,
    STATIC_SENSOR
  };
  
  PhysicsComponent(GameObject & gameObject, Type type);
  virtual ~PhysicsComponent();
  
  void setVx(float vx);
  void setVy(float vy);

  void addFx(float fx);
  void addFy(float fy);

  void postStep();

  void inline setPosition() { positionSet = true; }
  
private:

  b2Body* mBody;
  bool positionSet{false};

};

#endif
