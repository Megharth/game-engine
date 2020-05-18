#include "base/ResourceManager.hpp"
#include "res_path.hpp"



ResourceManager::ResourceManager() {

}

ResourceManager* ResourceManager::instance = 0;

ResourceManager& ResourceManager::getInstance() {
    if(instance == 0)
        instance = new ResourceManager();
    return *instance;
}

int ResourceManager::startUp() {
    surface = NULL;
    texture = NULL;
    font = NULL;
    return 0;
}



SDL_Texture* ResourceManager::load_texture(std::string fileName, SDL_Renderer* ren) {
    std::map<std::string, SDL_Texture*>::iterator x = textures.find(fileName);
    if(x != textures.end())
    {
        return (*x).second;
    }
    
    std::string res_path = getResourcePath() + fileName;
    const char* path = const_cast<char*>(res_path.c_str());

    surface = IMG_Load(path);
    if(surface == NULL) {
        std::cout << path << std::endl;
      SDL_Log("Failed to allocate surface");
    }
    else {
        texture = SDL_CreateTextureFromSurface(ren, surface);
        textures.insert(std::make_pair(fileName, texture));
    }
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture* ResourceManager::load_font(std::string fileName, int size, std::string message, 
    int lang, SDL_Color color, SDL_Renderer* ren) {

    std::map<std::string, SDL_Texture*>::iterator f = fonts.find(fileName+message+std::to_string(size));
    if(f != fonts.end())
        return (*f).second;


    const std::string res_path = getResourcePath() + fileName;
    const char* path = const_cast<char*>(res_path.c_str());
    font = TTF_OpenFont(path, size);
    if(font == NULL) {
        SDL_Log("Failed to open the font file");
        return NULL;
    }

    SDL_Surface *surf;
    SDL_Texture *text;
    std::string translation;
    

    surf = TTF_RenderUTF8_Blended(font, message.c_str(), color);
    if(surf == NULL) {
        std::cout << fileName << std::endl;
        SDL_Log("Failed to load surface for font file");
        return NULL;
    }

    text = SDL_CreateTextureFromSurface(ren, surf);
    if(text == NULL) {
        SDL_Log("Failed to load texture for font file");
        return NULL;
    }
    fonts.insert(std::make_pair(fileName+message+std::to_string(size), text));
    SDL_FreeSurface(surf);

    TTF_CloseFont(font);

    
    return text;
}

Mix_Chunk* ResourceManager::load_music(std::string musicfile){
	std::map<std::string, Mix_Chunk*>::iterator i = sounds.find(musicfile);
    if(i != sounds.end()) {
        return (*i).second;
    }

	std::string res_path = getResourcePath() + musicfile;
    Mix_Chunk* sound = Mix_LoadWAV(res_path.c_str());
    sounds.insert(std::make_pair(res_path, sound));
    return sound;
}

Mix_Music* ResourceManager::load_track(std::string trackfile){
	std::map<std::string, Mix_Music*>::iterator i = tracks.find(trackfile);
    if(i != tracks.end()) {
        return (*i).second;
    }

	std::string res_path = getResourcePath() + trackfile;
    Mix_Music* sound = Mix_LoadMUS(res_path.c_str());
    tracks.insert(std::make_pair(res_path, sound));
    return sound;
}

std::string* ResourceManager::load_level(std::string levelName) {
    std::map<std::string, std::string*>::iterator l = levels.find(levelName);
    if(l != levels.end())
        return l->second;
    std::string* levelDetails = new std::string[20];
    std::string line;
    int i = 0;
    std::ifstream config_file (getResourcePath() + levelName + ".config");
    
    if(config_file.is_open()) {
        while(getline(config_file, line)) {
            levelDetails[i] = line;
            i++;
        }
        levels.insert(std::make_pair(levelName, levelDetails));
    }

    return levelDetails;

}
int ResourceManager::unload_texture(std::string fileName) {
    std::map<std::string, SDL_Texture*>::iterator t = textures.find(fileName);
    if(t != textures.end()) {
        SDL_DestroyTexture((*t).second);
        textures.erase(t);
    }
    return 0;
}

int ResourceManager::unload_font(std::string fileName, int size, std::string message, int lang) {
    std::map<std::string, SDL_Texture*>::iterator f = fonts.find(fileName+message+std::to_string(size));
    if(f != fonts.end()) {
        SDL_DestroyTexture(f->second);
        fonts.erase(f);
    }
    return 0;
}

int ResourceManager::unload_track(std::string trackfile){
    std::map<std::string, Mix_Music*>::iterator i = tracks.find(trackfile);
    if(i != tracks.end()) {
        Mix_FreeMusic(i->second);
        tracks.erase(i);
    }
    return 0;
}

int ResourceManager::unload_music(std::string musicfile) {
    std::map<std::string, Mix_Chunk*>::iterator i = sounds.find(musicfile);
    if(i != sounds.end()) {
        Mix_FreeChunk(i->second);
        sounds.erase(i);
    }

    return 0;
}

void ResourceManager::settexturenull(){
	std::map<std::string, SDL_Texture*>::iterator t = textures.begin();
	    while(t != textures.end()) {
	        SDL_DestroyTexture((*t).second);
	        t = textures.erase(t);
	    }
	    texture = NULL;
}

int ResourceManager::shutDown() {
    std::map<std::string, SDL_Texture*>::iterator t = textures.begin();
    while(t != textures.end()) {
        SDL_DestroyTexture((*t).second);
        t = textures.erase(t);
    }

    std::map<std::string, SDL_Texture*>::iterator f = fonts.begin();
    while(f != fonts.end()) {
        f = fonts.erase(f);
    }

    std::map<std::string, Mix_Chunk*>::iterator i = sounds.begin();
    while(i != sounds.end()) {
        Mix_FreeChunk(i->second);
        i = sounds.erase(i);
    }

    std::map<std::string, Mix_Music*>::iterator tr = tracks.begin();
    while(tr != tracks.end()) {
        Mix_FreeMusic(tr->second);
        tr = tracks.erase(tr);
    }

    surface = NULL;
    texture = NULL;
    font = NULL;
    return 0;
}
