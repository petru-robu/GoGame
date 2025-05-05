#include "../inc/ui_elements.h"

Label::Label(sf::RenderWindow& window, const std::string& str = "text", float ch_size = 12, sf::Color color = sf::Color::Red, 
const std::string& font_path = "", sf::Vector2f position = {0,0}):
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
    auto loaded_font = ResourceManager::getInstance().getFont(font_path);
    
    if(loaded_font != nullptr)
        text.setFont(*loaded_font);

    text.setString(str);
    text.setCharacterSize(ch_size);
    text.setFillColor(color);

    calculatePosition();
}

/* Setters */
void Label::setColor(const sf::Color& col)
{
    color = col;
    text.setFillColor(col);
}

void Label::setPosition(sf::Vector2f pos)
{
    position = pos;
    text.setPosition(pos);
}

void Label::setString(const std::string& new_str)
{
    text.setString(new_str);
}

/* Getters */
sf::Vector2f Label::getPosition() const
{   
    return position;
}

sf::FloatRect Label::getBounds() const
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

    text.setFillColor(color);
    if(getBounds().contains({mx, my}))
        text.setFillColor(hoverColor);
}

Button::Button(sf::RenderWindow& window, const std::string& str, float ch_size, sf::Color color, 
    const std::string& font_path, sf::Vector2f position, bool hasBorders): 
    Label(window, str, ch_size, color, font_path, position)
    {
        borders = hasBorders;
        
        auto text_bounds = text.getGlobalBounds();
        border.setSize({text_bounds.size.x + 10, text_bounds.size.y + 10});
        border.setOrigin({border.getSize().x/2, border.getSize().y/2});
        border.setPosition(position);

        border.setOutlineColor(color);
        border.setFillColor(sf::Color(255, 255, 255, 0));
        border.setOutlineThickness(3.f);
    }

sf::FloatRect Button::getBounds() const
{
    if(borders == true)
        return border.getGlobalBounds();
    else
        return text.getGlobalBounds();
}

void Button::setColor(const sf::Color& col)
{
    Label::setColor(col);
    border.setOutlineColor(col);
}

void Button::setPosition(sf::Vector2f pos)
{
    Label::setPosition(pos);
    border.setPosition(pos);
}   

void Button::setString(const std::string &new_str)
{
    Label::setString(new_str);
    auto text_bounds = text.getGlobalBounds();
    border.setSize({text_bounds.size.x + 10, text_bounds.size.y + 10});
    border.setOrigin({border.getSize().x/2, border.getSize().y/2});
    border.setPosition(position);
}

void Button::setBorders(bool b)
{
    borders = b;
}

void Button::colorOnHover(sf::Vector2i mouse_pos, sf::Color hoverColor)
{
    float mx = mouse_pos.x;
    float my = mouse_pos.y;

    text.setFillColor(color);
    border.setOutlineColor(color);

    if(borders)
    {
        if(border.getGlobalBounds().contains({mx, my}))
        {
            text.setFillColor(hoverColor);
            border.setOutlineColor(hoverColor);
        }
    }
    else
    {
        if(text.getGlobalBounds().contains({mx, my}))
        {
            text.setFillColor(hoverColor);
            border.setOutlineColor(hoverColor);
        }
    }   
}

bool Button::hasBorders()
{
    return borders;
}

void Button::Render()
{
    window.draw(text);

    if(borders)
        window.draw(border);
}

void Button::HandleClick(const std::optional<sf::Event> &event)
{
    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            float mx = mouseButtonPressed->position.x;
            float my = mouseButtonPressed->position.y;

            if(this->getBounds().contains({mx, my}))
            {
                clicked = true;
                AudioPlayer::getInstance().playButtonSound();
            }
                
        }
    }
}

bool Button::WasClicked() const
{
    return clicked;
}

void Button::ResetClick()
{
    clicked = false;
}

