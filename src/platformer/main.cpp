#include "platformer/Platformer.hpp"

int
main(int _ac, char* av[]) {
    Platformer game(1280, 720);
    game.loop();
    return 0;
}
