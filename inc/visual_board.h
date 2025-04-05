#ifndef VISUAL_BOARD_H
#define VISUAL_BOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "game_context.h"
#include "drawable_interface.h"
#include "backend_board.h"
#include "ui_elements.h"

template <typename DT>
class Cell : public IDrawable
{
private:
    int coord_x, coord_y;

    float cell_size;
    sf::Vector2f position;
    
    DT drawable_cell;
    
public:
    Cell(sf::RenderWindow& window, int coord_x, int coord_y, int cell_size, sf::Vector2f pos);
    void setPosition(sf::Vector2f pos);

    DT getDrawableShape();
    void setColor(sf::Color color);
    int getCoordX();
    int getCoordY();

    void Render() override;

    virtual ~Cell();
};

class Piece: public Cell<sf::CircleShape>
{
private:
    bool hovered;
    bool placed;

public:
    Piece(sf::RenderWindow& window, int coord_x, int coord_y, int cell_size, sf::Vector2f pos);

    void setHovered(bool b);
    void setPlaced(bool b);
    bool isHovered();
    bool isPlaced();

    ~Piece() override;
};

class Liberty: public Cell<sf::RectangleShape>
{
private:
    bool placed;
    
public:
    Liberty(sf::RenderWindow& window, int coord_x, int coord_y, int cell_size, sf::Vector2f pos);
    ~Liberty() override;

    void setPlaced(bool b);
    bool isPlaced();
};


class VisualBoard: public IDrawable
{
private:
    GameContext& ctx;

    BackendBoard backend_board;

    sf::RectangleShape board_background;

    std::vector<sf::RectangleShape> grid_linesX;
    std::vector<sf::RectangleShape> grid_linesY;

    std::vector<std::vector<Piece>> piece_grid;
    std::vector<std::vector<Liberty>> liberty_grid;

    std::vector<Label*> intersection_numbers;
    std::vector<Label*> intersection_letters;

public:
    VisualBoard(sf::RenderWindow& window, GameContext &ctx);

    void process();
    void manageHovers(sf::Vector2i mouse_pos);
    void manageMouseClick(sf::Vector2i mouse_pos, int mouse_click_type);

    void Render() override;

    ~VisualBoard();

};
#endif