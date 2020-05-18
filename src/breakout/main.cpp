#include "breakout/breakout.hpp"

int
main(int _ac, char* av[]) {
    breakout game(1280, 720);
    game.loop();
    return 0;
}
