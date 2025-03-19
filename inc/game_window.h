#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "ui_elements.h"
#include "visual_board.h"
#include "menu_interface.h"

class GameWindow : public IMenu
{
private:
    VisualBoard visual_board;
    
public:
    GameWindow(sf::RenderWindow &window, GameContext &ctx);
    void EventHandler(const std::optional<sf::Event> &event);
    void Render();
    void Process();
};

#endif