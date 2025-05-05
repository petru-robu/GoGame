#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "ui_elements.h"
#include "visual_board.h"
#include "menu_interface.h"
#include "color_constants.h"

class LocalGameWindow : public IMenu
{
private:
    VisualBoard* visual_board;
    CellType turn;

    Label* title;
    Button* end_game_button;
    Button* clear_board_button;
    Button* options_menu_button;
    Button* pass_button;

    Label* to_play;
    Label* game_type_label; 

    std::vector<IDrawable*> ui_elements;

    sf::Sprite backgroundSprite;
    
public:
    LocalGameWindow(sf::RenderWindow &window);
    void EventHandler(const std::optional<sf::Event> &event) override;
    void Render() override;
    void Process() override;

    LocalGameWindow(const LocalGameWindow& game) = delete;
    LocalGameWindow& operator=(const LocalGameWindow& game) = delete;

    ~LocalGameWindow() override;
};

class AIGameWindow : public IMenu
{
private:
    VisualBoard* visual_board;
    CellType turn;

    Label* title;
    Button* end_game_button;
    Button* clear_board_button;
    Button* options_menu_button;
    
    Label* game_type_label;

    std::vector<IDrawable*> ui_elements;

    sf::Sprite backgroundSprite;
    
public:
    AIGameWindow(sf::RenderWindow &window);
    void EventHandler(const std::optional<sf::Event> &event) override;
    void Render() override;
    void Process() override;

    AIGameWindow(const AIGameWindow& game) = delete;
    AIGameWindow& operator=(const AIGameWindow& game) = delete;

    ~AIGameWindow() override;
};

#endif