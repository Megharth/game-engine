#include "base/TextureRendererComponent.hpp"
#include <iostream>
TextureRendererComponent::TextureRendererComponent(GameObject & gameObject, SDL_Texture* tex):
    RenderComponent(gameObject), texture(tex) {}

void TextureRendererComponent::render(SDL_Renderer* renderer) {
    std::cout << "rendering...\n";
}