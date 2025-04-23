#ifndef MENUS_H
#define MENUS_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "ui_elements.h"
#include "menu_interface.h"
#include "color_constants.h"

class MainMenu : public IMenu
{
private:
    Label title;
    Label play_button;
    Label options_button;
    Label exit_button;

    sf::Sprite backgroundSprite;

public:
    MainMenu(sf::RenderWindow &window, GameContext &ctx);

    void Render() override;
    void Process() override;
    void EventHandler(const std::optional<sf::Event> &event) override;
};


class OptionsMenu : public IMenu
{
private:
    Label back_button;
    
    sf::Sprite backgroundSprite;
public:
    OptionsMenu(sf::RenderWindow &window, GameContext &ctx);

    void Render() override;
    void Process() override;
    void EventHandler(const std::optional<sf::Event> &event) override;
};

class SelectorMenu : public IMenu
{
private:
    Label select_board_size;
    Label select_game_type;
    Label play_button;
    Label back_button;

    LabelBox l_9x9;
    LabelBox l_13x13;
    LabelBox l_19x19;

    LabelBox l_AI;
    LabelBox l_LOCAL;
    

    sf::Sprite backgroundSprite;

    int curr_game_size;
    GameType curr_game_mode;

public:
    SelectorMenu(sf::RenderWindow &window, GameContext &ctx);

    void Render() override;
    void Process() override;
    void EventHandler(const std::optional<sf::Event> &event) override;
};

#endif