#include "base/RectRenderComponent.hpp"
#include "base/GameObject.hpp"

RectRenderComponent::RectRenderComponent(GameObject & gameObject, Uint8 r, Uint8 g, Uint8 b):
  RenderComponent(gameObject),
  mR(r),
  mG(g),
  mB(b)
{
}

void
RectRenderComponent::render(SDL_Renderer * renderer) const
{
  SDL_Rect fillRect = { int(getGameObject().x()), int(getGameObject().y()), int(getGameObject().w()), int(getGameObject().h()) };
  SDL_SetRenderDrawColor(renderer, mR, mG, mB, 0xFF);
  SDL_RenderFillRect(renderer, &fillRect);
}
