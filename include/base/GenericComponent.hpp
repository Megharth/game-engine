#ifndef BASE_GENERIC_COMPONENT
#define BASE_GENERIC_COMPONENT

#include "base/Component.hpp"
#include <memory>

class Level;

//! \brief A generic component that can handle updating and collisions.
class GenericComponent: public Component {
public:
  
  GenericComponent(GameObject & gameObject);

  virtual void update(Level & level); //!< Update the object.
  virtual void update(Level & level, bool b);
  virtual void collision(Level & level, std::shared_ptr<GameObject> obj); //!< Handle a collision with the given object.

};

#endif
