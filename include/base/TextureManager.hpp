#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SDL.h>
#include <string>

//! Manage texture
class TextureManager {
private:
    TextureManager() = default;
    TextureManager(TextureManager const&) = delete;
    void operator=(TextureManager const&) = delete;
public:
    static TextureManager &getInstance();
    void renderTexture(SDL_Texture*, SDL_Renderer*, int, int, int, int);
    void renderTexture(SDL_Texture*, SDL_Renderer*, int, int);
    SDL_Texture* renderText(const std::string &, const std::string &, int, SDL_Color, int, SDL_Renderer*);
};

#endif
