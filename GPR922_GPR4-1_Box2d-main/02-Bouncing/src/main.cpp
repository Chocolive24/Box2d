#include <iostream>

#include "game.h"

int main()
{
    Game game;
    
    // Initiate the game
    game.init();

    // Then loop for ever
    game.loop();

    return EXIT_SUCCESS;
}
