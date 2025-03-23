#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "menus.h"
#include "game_context.h"
#include "game_window.h"
#include "menu_interface.h"

class Game
{
private:
    sf::RenderWindow window;
    GameContext ctx;

    IMenu* menu;
    OptionsMenu* options_menu;
    MainMenu* main_menu;
    GameWindow* game_window;

    void Init();
    void changeState();
    

public:
    Game();
    
    Game(const Game& game) = delete;
    Game& operator=(const Game& game) = delete;

    ~Game();
    void Run();
};


#endif