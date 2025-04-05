#ifndef DRAWABLE_INTERFACE_H
#define DRAWABLE_INTERFACE_H

#include <SFML/Graphics.hpp>

class IDrawable
{
protected:
    sf::RenderWindow& window;

public:
    IDrawable(sf::RenderWindow& window): window(window){}
    virtual void Render() = 0;
    virtual ~IDrawable() = default;
};

#endif