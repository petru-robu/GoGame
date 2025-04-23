#ifndef UI_ELEMENTS_H
#define UI_ELEMENTS_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "game_context.h"
#include "menu_interface.h"
#include "drawable_interface.h"
#include "resource_manager.h"

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
    Label(sf::RenderWindow& window, const std::string& str, float ch_size, sf::Color color, 
    const std::string& font_path, sf::Vector2f position);

    virtual sf::Vector2f getPosition() const;
    virtual sf::FloatRect getBounds() const;

    virtual void setColor(const sf::Color& col);
    virtual void setPosition(sf::Vector2f pos);
    virtual void setString(const std::string& new_str);

    virtual void colorOnHover(sf::Vector2i mouse_pos, sf::Color hoverColor);

    void Render() override;

    ~Label() override = default;
};

class LabelBox: public Label
{
protected:
    bool borders;
    sf::RectangleShape border;

public:
    LabelBox(sf::RenderWindow& window, const std::string& str, float ch_size, sf::Color color, 
    const std::string& font_path, sf::Vector2f position, bool borders);

    sf::FloatRect getBounds() const override;

    void setColor(const sf::Color& col) override;
    void setPosition(sf::Vector2f pos) override;
    void setString(const std::string& new_str) override;
    void setBorders(bool borders);

    void colorOnHover(sf::Vector2i mouse_pos, sf::Color hoverColor) override;

    void Render() override;

    ~LabelBox() override = default;
};


#endif