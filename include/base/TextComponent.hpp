#ifndef TEXT_COMPONENT_HPP
#define TEXT_COMPONENT_HPP

#include <SDL.h>
#include <base/ResourceManager.hpp>
#include "base/GameObject.hpp"
#include "base/TextRenderComponent.hpp"

//! Game Object of Text component type
class TextComponent : public GameObject {
private: 
    SDL_Texture* texture;

public:
    TextComponent(Level &, const std::string &, SDL_Color, int, int, int, int, int, SDL_Renderer*);
    ~TextComponent();
};

#endif
