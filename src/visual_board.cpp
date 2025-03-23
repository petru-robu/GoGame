#include "../inc/visual_board.h"

template <typename DT> 
Cell<DT>::Cell(sf::RenderWindow& window, int coord_x, int coord_y, int cell_size, sf::Vector2f pos):
IDrawable(window), coord_x(coord_x), coord_y(coord_y), 
cell_size(cell_size), position(pos)
{
    if constexpr (std::is_same_v<DT, sf::CircleShape>)
        drawable_cell.setRadius(cell_size / 2);
    else
    {
        drawable_cell.setSize({cell_size, cell_size});
    }
    
    drawable_cell.setPosition(position);
}

/*Setters & Getters*/
template <typename DT> 
void Cell<DT>::setPosition(sf::Vector2f pos)
{
    position = pos;
}

template <typename DT> 
DT Cell<DT>::getDrawableShape()
{
    return drawable_cell;
}

template <typename DT> 
int Cell<DT>::getCoordX()
{
    return coord_x;
}

template <typename DT> 
int Cell<DT>::getCoordY()
{
    return coord_y;
}

template <typename DT> 
void Cell<DT>::setColor(sf::Color color)
{
    drawable_cell.setFillColor(color);
}


template <typename DT> 
void Cell<DT>::Render()
{
    window.draw(drawable_cell);
}

Piece::Piece(sf::RenderWindow& window, int coord_x, int coord_y, int cell_size, sf::Vector2f pos): 
Cell<sf::CircleShape>(window, coord_x, coord_y, cell_size, pos)
{
    hovered = placed = false;
}

/*Setters & Getters*/
void Piece::setHovered(bool b)
{
    hovered = b;
}
void Piece::setPlaced(bool b)
{
    placed = b;
}
bool Piece::isHovered()
{
    return hovered;
}
bool Piece::isPlaced()
{
    return placed;
}


VisualBoard::VisualBoard(sf::RenderWindow& window, GameContext& ctx): 
IDrawable(window), ctx(ctx), bb(ctx)
{
    float board_size = 900;
    float cornerX = 500, cornerY = 10;
    int game_size = ctx.getGameSize();
    
    float cell_size = board_size / game_size;

    board_background.setFillColor(sf::Color(252, 144, 3));
    board_background.setSize({board_size, board_size});
    board_background.setPosition({cornerX, cornerY});


    /*piece grid*/
    for(int i=0; i<game_size; i++)
    {
        std::vector<Piece> cell_line;
        for(int j=0; j<game_size; j++)
        {
            float currX = cornerX + (i)*cell_size;
            float currY = cornerY + (j)*cell_size;
            
            Piece piece(window, i, j, cell_size, {currX, currY});
            piece.setColor(sf::Color::Black);
            cell_line.push_back(piece);
        }
        piece_grid.push_back(cell_line);
    }

    cornerX += cell_size/2;
    cornerY += cell_size/2;

    for(int i=0; i<game_size; i++)
    {
        sf::RectangleShape grid_line_x;
        grid_line_x.setFillColor(sf::Color(31, 17, 0));
        grid_line_x.setSize({2, cell_size*(game_size-1)});
        grid_line_x.setPosition({cornerX + (i)*cell_size, cornerY});
        grid_linesX.push_back(grid_line_x);

        sf::RectangleShape grid_line_y;
        grid_line_y.setFillColor(sf::Color(31, 17, 0));
        grid_line_y.setSize({cell_size*(game_size-1), 2});
        grid_line_y.setPosition({cornerX, cornerY + (i)*cell_size});
        grid_linesY.push_back(grid_line_y);
    }

}

void VisualBoard::manageHovers(sf::Vector2i mouse_pos)
{
    float mx = mouse_pos.x;
    float my = mouse_pos.y;

    for(auto &vec:piece_grid)
    {
        for(auto &cell:vec)
        {
            if(!cell.isPlaced() && cell.getDrawableShape().getGlobalBounds().contains({mx,my}))
            {   
                cell.setHovered(true);
                cell.setColor(sf::Color(255,0,0,200));
            }
            else
            {
                cell.setHovered(false);
            }
        }       
    }
}

void VisualBoard::manageMouseClick(sf::Vector2i mouse_pos, int mouse_click_type)
{
    float mx = mouse_pos.x;
    float my = mouse_pos.y;

    for(auto &vec:piece_grid)
    {
        for(auto &cell:vec)
        {
            if(cell.getDrawableShape().getGlobalBounds().contains({mx,my}))
            {
                int cx = cell.getCoordX();
                int cy = cell.getCoordY();
                
                bb.addStone(cx, cy, mouse_click_type);
            }
        }       
    }
}

void VisualBoard::process()
{
    std::vector<std::vector<int>> board_matrix = bb.getBoardMatrix();
    int gs = ctx.getGameSize();

    for(int i=0; i<gs; i++)
        for(int j=0; j<gs; j++)
        {
            int val = board_matrix[i][j];
            if(val != -1)
            {
                piece_grid[i][j].setPlaced(true);

                if(val == 0)
                {
                    piece_grid[i][j].setColor(sf::Color::Black);
                }
                else if(val == 1)
                {
                    piece_grid[i][j].setColor(sf::Color::White);
                }
            }
        }

}

void VisualBoard::Render()
{
    window.draw(board_background);

    for(auto &line:grid_linesX)
        window.draw(line);
    
    for(auto &line:grid_linesY)
        window.draw(line);


    for(auto &line:piece_grid)
    {
        for(auto &piece:line)
        {
            if(piece.isPlaced() || piece.isHovered())
                window.draw(piece.getDrawableShape());
        }
    }
}