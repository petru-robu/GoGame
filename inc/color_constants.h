#ifndef COLORS_H
#define COLORS_H

#include <SFML/Graphics.hpp>

namespace Colors
{
    const sf::Color RED      = sf::Color(255, 0, 0, 255);
    const sf::Color GREEN    = sf::Color(0, 255, 0, 255);
    const sf::Color BLUE     = sf::Color(0, 0, 255, 255);
    const sf::Color WHITE    = sf::Color(255, 255, 255, 255);
    const sf::Color BLACK    = sf::Color(0, 0, 0, 255);

    const sf::Color TEXT_HOVER_COLOR = sf::Color(255, 174, 0, 180);
    const sf::Color BUTTON_COLOR = sf::Color(255, 174, 0);
    const sf::Color TITLE_COLOR = sf::Color(235, 240, 255);

    const sf::Color BOARD_BACKGROUND_COLOR = sf::Color(252, 144, 3);
    const sf::Color GRID_LINE_COLOR = sf::Color(31, 17, 0);
    const sf::Color PIECE_HOVER_COLOR = sf::Color(255, 0, 0, 100);
    const sf::Color LIBERTY_COLOR = sf::Color(255, 234, 0);
}


#endif