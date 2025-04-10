#include "../inc/ui_elements.h"

Label::Label(sf::RenderWindow& window, std::string str = "text", float ch_size = 12, sf::Color color = sf::Color::Red, 
std::string font_path = "", sf::Vector2f position = {0,0}):
IDrawable(window),
str(str), ch_size(ch_size), color(color), font_path(font_path),
position(position), text(font, "", 10)
{
    loadProprieties();
}

void Label::calculatePosition()
{
    sf::FloatRect tr = text.getLocalBounds();
    text.setOrigin(tr.position + tr.size / 2.f);
    text.setPosition(position);
}

void Label::loadProprieties()
{
    if(!font.openFromFile(font_path))
        std::cerr<<"Cannot open font!";
    
    text.setString(str);
    text.setFont(font);
    text.setCharacterSize(ch_size);
    text.setFillColor(color);

    calculatePosition();
}

/* Setters */
void Label::setColor(sf::Color c)
{
    color = c;
    text.setFillColor(color);
}

void Label::setPosition(sf::Vector2f pos)
{
    position = pos;
    text.setPosition(position);
}

void Label::setString(std::string new_str)
{
    text.setString(new_str);
}

/* Getters */
sf::Vector2f Label::getPosition()
{   
    return position;
}

sf::FloatRect Label::getBounds()
{
    return text.getGlobalBounds();
}

void Label::Render()
{
    window.draw(text);
}

void Label::colorOnHover(sf::Vector2i mouse_pos, sf::Color hoverColor)
{
    float mx = mouse_pos.x;
    float my = mouse_pos.y;

    setColor(sf::Color::White);
    if(getBounds().contains({mx, my}))
        setColor(hoverColor);
}