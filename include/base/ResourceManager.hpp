/**
 * ResourceManager.hpp
 * Author: Megharth
 */

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <map>
#include <iterator>
#include <fstream>
#include <string>
#include <memory>
#include <cstring>


//! \brief  A class for managing game resources.  Allows access to resources
//!  and makes sure there is only one copy of each resource loaded at a
//!  time.


class ResourceManager {
private:
    ResourceManager();  // Private Singleton
    ResourceManager(ResourceManager const&) = delete; // Avoid copy constructor.
    void operator=(ResourceManager const&) = delete; // Don't allow copy assignment.
    ResourceManager(ResourceManager const&&) = delete; // Avoid move constructor.
    void operator=(ResourceManager const&&) = delete; // Don't allow move assignment
    
    SDL_Surface* surface;
    SDL_Texture* texture;
    TTF_Font* font;
    static ResourceManager* instance;
    
    std::map<std::string, SDL_Texture*> textures;
    std::map<std::string, SDL_Surface*> surfaces; 
    std::map<std::string, SDL_Texture*> fonts;
    std::map<std::string, Mix_Chunk*> sounds;
    std::map<std::string, Mix_Music*>tracks;
    std::map<std::string, std::string*>levels;
    
public:
    /**
     * This makes sure that the resource manager is a singleton and provides only
     * a signle instance for the entire project so that resources can be shared
     * accross multiple classes.
     */
    static ResourceManager &getInstance();
    
    /** 
     * 'equivalent' to our constructor. Provides control to the user for starting 
     * up the resource manager.
     */
    int startUp();
    
    /** 'equivalent' to our destructor. Provides control to the user for shutting
     *  down the resource manager.
     */
    int shutDown();

    /**
     * This is used to load textures. Resource manager will load the texture and
     * save it in a map. So, that in future, if the same resource is requested, it
     * can be retrieved from the map instead of loading it all over again.
     */
    SDL_Texture* load_texture(std::string, SDL_Renderer*);


    /**
     * To load font texture so that it can be reused.
     */
    SDL_Texture* load_font(std::string, int, std::string, int, SDL_Color, SDL_Renderer*);


     /**
     * loads music into the game
     */
    Mix_Chunk* load_music(std::string musicfile);

    /**
     * loads music track
     */
    Mix_Music* load_track(std::string trackfile);

    /**
     * This is used to unload a texture from the resource manager.
     */


    /**
     * loads the level from the config file
     */
    std::string* load_level(std::string);

    /**
     * unloads the texture from map and destroys the texture
     */
    int unload_texture(std::string);

    /**
     * unloads font from map
     */
    int unload_font(std::string, int,std::string, int);

    /**
     * unloads music
     */
    int unload_music(std::string musicfile);

    /**
     * unloads music track
     */
    int unload_track(std::string musicfile);

    /**
     * unloads the level from map
     */
    int unload_level(std::string);

    void settexturenull();

};

#endif
