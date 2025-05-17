#ifndef THEME_H
#define THEME_H

#include <SFML/Graphics.hpp>
#include "color_constants.h"

enum class ThemeType {LIGHT, DARK};

struct Theme
{
    ThemeType type;
    sf::Color boardColor;
    sf::Color lineColor;
    sf::Color pieceHoverColor;
    sf::Color libertyColor;
};

extern Theme lightTheme;
extern Theme darkTheme;



#endif