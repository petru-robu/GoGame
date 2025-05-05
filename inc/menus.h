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
    Label *title;
    Button *play_button;
    Button *options_button;
    Button *exit_button;

    std::vector<IDrawable*> ui_elements;

    sf::Sprite backgroundSprite;

public:
    explicit MainMenu(sf::RenderWindow &window);

    void Render() override;
    void Process() override;
    void EventHandler(const std::optional<sf::Event> &event) override;

    MainMenu(const MainMenu&) = delete;
    void operator=(const MainMenu&) = delete;
    ~MainMenu() override;
};


class OptionsMenu : public IMenu
{
private:
    Button* back_button;

    Label* sounds_enabled;
    Button* sounds_enabled_on, *sounds_enabled_off;

    Label* music_enabled;
    Button* music_enabled_on, *music_enabled_off;

    Label* liberties_enabled;
    Button* liberties_enabled_on, *liberties_enabled_off;
    
    std::vector<IDrawable*> ui_elements;

    sf::Sprite backgroundSprite;
public:
    explicit OptionsMenu(sf::RenderWindow &window);

    void Render() override;
    void Process() override;
    void EventHandler(const std::optional<sf::Event> &event) override;

    OptionsMenu(const OptionsMenu&) = delete;
    void operator=(const OptionsMenu&) = delete;
    ~OptionsMenu() override;
};

class SelectorMenu : public IMenu
{
private:
    Label* select_board_size;
    Label* select_game_type;
    Button* play_button;
    Button* back_button;

    Button* l_9x9;
    Button* l_13x13;
    Button* l_19x19;

    Button* l_AI;
    Button* l_LOCAL;
    
    std::vector<IDrawable*> ui_elements;

    sf::Sprite backgroundSprite;

    int curr_game_size;
    GameType curr_game_mode;

public:
    explicit SelectorMenu(sf::RenderWindow &window);

    void Render() override;
    void Process() override;
    void EventHandler(const std::optional<sf::Event> &event) override;

    SelectorMenu(const SelectorMenu&) = delete;
    void operator=(const SelectorMenu&) = delete;
    ~SelectorMenu() override;
};

#endif