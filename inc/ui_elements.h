#ifndef UI_ELEMENTS_H
#define UI_ELEMENTS_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "game_context.h"
#include "menu_interface.h"
#include "drawable_interface.h"

class Label: public IDrawable
{
protected:
    std::string str;
    float ch_size;
    sf::Color color;
    std::string font_path;
    sf::Vector2f position;
    
    sf::Font font;
    sf::Text text;

    void calculatePosition();
    void loadProprieties();

public:
    Label(sf::RenderWindow& window, std::string str, float ch_size, sf::Color color, 
    std::string font_path, sf::Vector2f position);

    sf::Vector2f getPosition();
    sf::FloatRect getBounds();

    void setColor(sf::Color color);
    void setPosition(sf::Vector2f position);

    void colorOnHover(sf::Vector2i mouse_pos, sf::Color hoverColor);

    void Render() override;

    ~Label() = default;
};



#endif