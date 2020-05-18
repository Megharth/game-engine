# Game Engine

A base setup of a Game Engine using C++. This summarizes everything that I have learned in class CS5850 at Northeastern University. I have developed three games using the same engine and it can be found in their respective branches. All of these games are fairly optimized to run at 60 FPS and are integrated with Box2D Physics engine. Have implemented a resource manager, sound manager and physics manager as a part of the base of game engine to utilize the resource for the game efficiently. Contains Input manager to effectively register player's input and respond to that input with minimal lag. The engine is developed with component based system to divide the functionalities among various components and then use them as needed. 

The games are:

#### Breakout
  - A basic breakout game with 3 unique levels.
  - Offers 3 lives throughout the game.
  - Player needs to destroy each brick in the current level to go the next level.
  - Player loses a life if they miss to catch the ball with paddle.
  - Contains an engaging background music and sounds for different interactions throughout the game.
  - Can pause / unpause and reset game.
    
#### Skull Saga 
  - A "Mario" style platformer game in which you need to collect the collectibles to increase your score and reach to the goal.
  - Offers 3 lives throughout the game.
  - Has enemies with minimal AI that gaurds / patrols near the collectible.
  - Contains animations for the characters in game to make it look visually aesthetic and pleasing. 
  - Player will lose a life if enemy catches them.
  - Has three unique levels.
  - Features springs and boosts as environmental objects. If the player steps on spring them will be able to jump higher and if they come in contact with boost, they will be given a temporary boost in left / right direction.
  - Contains an engaging background music and sounds for different interactions throughout the game.
  - Can pause / unpause and reset game.
    
#### Bomberman
  - A minimalized version of classic Bomberman game.
  - Offers 3 lives throught the game.
  - Has enemies with minimal AI that gaurds / patrols in certain areas.
  - Need to destroy the walls to make the way to the goal.
  - Has health power ups that increases the player life but these power ups can be found only by destroying walls.
  - Similarly, in order to go to next level, player will need to reach the goal, and the goal can be found only by destroying walls.
  - Has a hint feature, which helps player to find the goal and powerups.
  - Player can place bombs multiple time without having to wait for previous bomb to explode.
  - Player can control the explosion of bomb with a dedicated key or can let the bomb explode by itself.
  - Some of the walls in the game are stronger than others and thus needs two bomb explosions to destroy them.
  - Player will lose life if the enemy catches up or is by the explosion of bomb.
  - Contains animations for the characters in game to make it look visually aesthetic and pleasing. 
  - Contains an engaging background music and sounds for different interactions throughout the game.
  - Can pause / unpause and reset game
  
### Dependencies

_Note : These games can be built on linux or windows machine._

#### Linux

You will need to download and install C++ tools and SDL2 (including extension libraries) 

#### Windows

  - C++ tools: Use MinGW.
    - From the [MinGW page](www.mingw.org) download and run mingw-get-setup.exe.
    - In the Instalation Manager, under "Basic Setup" packages, mark mingw-developer-toolkit-bin, mingw32-base-bin, mingw32-gcc-g++-bin, and msys-base-bin, then choose Installation -> Apply Changes.
    - Use the Windows search bar to find "Edit the system environment variables." Click "Environment variables...". Add or edit the PATH variable to the System variables entry to add two new entries for "C:\MinGW\bin\" and "C:\MinGW\msys\1.0\bin\". Move these two entries to the top. (You may need to reboot for this to take effect.)
  - SDL2
    - Download the MinGW development libraries for [SDL](https://www.libsdl.org/download-2.0.php), [SDL_image](https://www.libsdl.org/projects/SDL_image/), [SDL_mixer](https://www.libsdl.org/projects/SDL_mixer/), and [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/)
    - Put the below PowerShell script in the same folder as the ".tar.gz" files you downloaded. Right click on the script and choose "Run with PowerShell".
    ```
    tar xpvzf SDL2-devel-2.0.10-mingw.tar.gz
    cd SDL2-2.0.10
    make native
    cd ..
    rm -r -fo SDL2-2.0.10

    tar xpvzf SDL2_image-devel-2.0.5-mingw.tar.gz
    cd SDL2_image-2.0.5
    make native
    cd ..
    rm -r -fo SDL2_image-2.0.5

    tar xpvzf SDL2_mixer-devel-2.0.4-mingw.tar.gz
    cd SDL2_mixer-2.0.4
    make native
    cd ..
    rm -r -fo SDL2_mixer-2.0.4

    tar xpvzf SDL2_ttf-devel-2.0.15-mingw.tar.gz
    cd SDL2_ttf-2.0.15
    make native
    cd ..
    rm -r -fo SDL2_ttf-2.0.15
    ```
  
  
