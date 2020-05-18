#ifndef BASE_RENDER_COMPONENT
#define BASE_RENDER_COMPONENT

#include "base/Component.hpp"
#include <SDL.h>

//! \brief A component that handles rendering.
class RenderComponent: public Component {
public:
  
  RenderComponent(GameObject & gameObject);

  virtual void render(SDL_Renderer * renderer) {}; //!< Do the render.
  virtual void render(SDL_Renderer * renderer , bool b) {};

};

#endif
