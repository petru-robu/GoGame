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

class IClickable
{
public:
    virtual void HandleClick(const std::optional<sf::Event> &event) = 0;
    virtual bool WasClicked() const = 0;
    virtual void ResetClick() = 0;
    virtual ~IClickable() = default;
};

#endif