#include <SFML/Graphics.hpp>
#include "../inc/game.h"

int main()
{
    Game& game = Game::getInstance();
    game.Run();
    
    return 0;
}
