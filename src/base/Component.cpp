#include "base/Component.hpp"

Component::Component(GameObject & gameObject):
  mGameObject(gameObject)
{
  (void) mGameObject; // to prevent warnings
}

Component::~Component()
{
}
