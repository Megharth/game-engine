#include "base/TextRenderComponent.hpp"

TextRenderComponent::TextRenderComponent(GameObject & gameObject, SDL_Texture* tex):
    RenderComponent(gameObject),
    texture(tex) {}

void TextRenderComponent::render(SDL_Renderer* renderer) {
    dest.x = getGameObject().x();
    dest.y = getGameObject().y();
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    dest.w = w;
    dest.h = h;
    int rv = SDL_RenderCopy(renderer, texture, NULL, &dest);
    if(rv != 0) {
        std::cout << "Some error in text render: " << rv << "\n";
    }
}
