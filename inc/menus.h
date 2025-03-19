#ifndef MENUS_H
#define MENUS_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "ui_elements.h"
#include "menu_interface.h"

class MainMenu : public IMenu
{
private:
    Label title;
    Label play_button;
    Label options_button;
    Label exit_button;

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

public:
    OptionsMenu(sf::RenderWindow &window, GameContext &ctx);

    void Render() override;
    void Process() override;
    void EventHandler(const std::optional<sf::Event> &event) override;
    
};

#endif