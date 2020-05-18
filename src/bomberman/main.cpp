#include "bomberman/bomberman.hpp"

int
main(int _ac, char* _av[]) {
    bomberman game(1280, 720);
    game.loop();
    return 0;
}
