#include "base/TextComponent.hpp"

TextComponent::TextComponent(Level & level, const std::string & message, SDL_Color color, int size, int x, int y, int w, int h, SDL_Renderer* renderer):
    GameObject(level, x, y, w, h, 99) {
        texture = ResourceManager::getInstance().load_font("fonts/Asar-Regular.ttf", size, message, 1, color, renderer);
        setRenderCompenent(std::make_shared<TextRenderComponent>(*this, texture));

}

TextComponent::~TextComponent() {
    texture = NULL;
}