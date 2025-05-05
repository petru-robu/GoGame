#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "menus.h"
#include "game_context.h"
#include "game_window.h"
#include "menu_interface.h"
#include "audio_player.h"

class Game
{
private:
    sf::RenderWindow window;
    GameContext ctx;
    AudioPlayer audio_player;

    IMenu* menu;
    OptionsMenu* options_menu;
    MainMenu* main_menu;
    SelectorMenu* selector_menu;

    LocalGameWindow* local_game_window;
    AIGameWindow* ai_game_window;
    
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