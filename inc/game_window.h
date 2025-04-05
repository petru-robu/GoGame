#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "ui_elements.h"
#include "visual_board.h"
#include "menu_interface.h"

class GameWindow : public IMenu
{
private:
    VisualBoard* visual_board;
    CellType turn;

    Label title;
    Label end_game_button;
    Label clear_board_button;
    Label back_to_menu;

    Label to_play;
    Label game_type_label;
    
public:
    GameWindow(sf::RenderWindow &window, GameContext &ctx);
    void EventHandler(const std::optional<sf::Event> &event) override;
    void Render() override;
    void Process() override;
    ~GameWindow() override;
};

#endif