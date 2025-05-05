#ifndef MENU_INTERFACE_H
#define MENU_INTERFACE_H

#include <SFML/Graphics.hpp>
#include "game_context.h"

class IMenu
{
protected:
    sf::RenderWindow& window;
    
public:
    IMenu(sf::RenderWindow& window): window(window){}
    
    virtual void Render() = 0;
    virtual void Process() = 0;
    virtual void EventHandler(const std::optional<sf::Event> &event) = 0;

    virtual ~IMenu() = default;
    
};

#endif