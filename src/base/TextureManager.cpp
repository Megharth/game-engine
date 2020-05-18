#include "base/TextureManager.hpp"
#include "base/ResourceManager.hpp"
TextureManager&
TextureManager::getInstance() {
    static TextureManager * instance = new TextureManager();
    return *instance;
}

void TextureManager::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void TextureManager::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

SDL_Texture* TextureManager::renderText(
    const std::string &message, const std::string &fileName, int lang,
    SDL_Color color, int fontSize, SDL_Renderer* renderer) {
    
    SDL_Texture* text = ResourceManager::getInstance().load_font(
        fileName, fontSize, message, lang, color, renderer);
    return text;
}
