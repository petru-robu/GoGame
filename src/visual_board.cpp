#include "../inc/visual_board.h"

template <typename DT> 
Cell<DT>::Cell(sf::RenderWindow& window, int coord_x, int coord_y, int cell_size, sf::Vector2f pos):
IDrawable(window), coord_x(coord_x), coord_y(coord_y), 
cell_size(cell_size), position(pos)
{
    if constexpr (std::is_same_v<DT, sf::CircleShape>)
    {
        drawable_cell.setRadius(cell_size / 2);
        drawable_cell.setPosition(position);
    }
    else
    {
        drawable_cell.setSize({float(cell_size), float(cell_size)});
        drawable_cell.setPosition({position.x + cell_size/2, position.y + cell_size/2});
    }

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

/*Piece*/
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
Piece::~Piece()
{
    
}

/*Liberty*/
Liberty::Liberty(sf::RenderWindow& window, int coord_x, int coord_y, int cell_size, sf::Vector2f pos):
Cell<sf::RectangleShape>(window, coord_x, coord_y, cell_size/2, pos)
{
    placed = false;
}

void Liberty::setPlaced(bool p)
{
    placed = p;
}
bool Liberty::isPlaced()
{
    return placed;
}

Liberty::~Liberty()
{

}

VisualBoard::VisualBoard(sf::RenderWindow& window, GameContext& ctx): 
IDrawable(window), ctx(ctx), backend_board(ctx)
{
    float board_size = 800;
    float cornerX = 570, cornerY = 90;
    int game_size = ctx.getGameSize();
    
    float cell_size = board_size / game_size;

    board_background.setFillColor(sf::Color(252, 144, 3));
    board_background.setSize({board_size+100, board_size+100});
    board_background.setPosition({cornerX-50, cornerY-50});

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

    for(int i=0; i<game_size; i++)
    {
        std::vector<Liberty> cell_line;
        for(int j=0; j<game_size; j++)
        {
            float currX = cornerX + (i)*cell_size;
            float currY = cornerY + (j)*cell_size;
            
            Liberty lib(window, i, j, cell_size, {currX, currY});
            lib.setColor(sf::Color::Black);
            cell_line.push_back(lib);
        }
        liberty_grid.push_back(cell_line);
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

        intersection_numbers.push_back(new Label(window, std::to_string(game_size - i), 25, 
        sf::Color::Black, "fonts/arial-bold.ttf", {cornerX - 45, cornerY + (i)*cell_size}));
        
        intersection_letters.push_back(new Label(window, std::string(1, 'A'+i), 25, 
        sf::Color::Black, "fonts/arial-bold.ttf", {cornerX + (i)*cell_size, cornerY - 45}));

    }
}

BackendBoard& VisualBoard::getBackendBoard()
{
    return backend_board;
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

void VisualBoard::manageMouseClick(sf::Vector2i mouse_pos, CellType& turn)
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

                bool move_state = backend_board.addStone(cx, cy, turn);
                if(move_state == true)
                {
                    //next player turn
                    if(turn == CellType::WHITE)
                    {
                        turn = CellType::BLACK;
                    }   
                    else if(turn == CellType::BLACK)
                    {
                        turn = CellType::WHITE;
                    }
                }
            }
        }       
    }
}

void VisualBoard::process()
{
    std::vector<std::vector<Intersection>> board_matrix = backend_board.getBoardMatrix();
    int gs = ctx.getGameSize();

    for(int i=0; i<gs; i++)
        for(int j=0; j<gs; j++)
        {
            CellType cell_type = board_matrix[i][j].getType();

            if(cell_type == CellType::BLACK || cell_type == CellType::WHITE)
            {
                piece_grid[i][j].setPlaced(true);

                if(cell_type == CellType::BLACK)
                {
                    piece_grid[i][j].setColor(sf::Color::Black);
                }
                else if(cell_type == CellType::WHITE)
                {
                    piece_grid[i][j].setColor(sf::Color::White);
                }
            }
            else
                piece_grid[i][j].setPlaced(false);
            

            if(cell_type == CellType::LIBERTY)
            {
                liberty_grid[i][j].setPlaced(true);
                liberty_grid[i][j].setColor(sf::Color::Yellow);
            }
            else
                liberty_grid[i][j].setPlaced(false);
        }

}

void VisualBoard::Render()
{
    window.draw(board_background);

    for(auto &nmb:intersection_numbers)
        nmb->Render();

    for(auto &lett:intersection_letters)
        lett->Render();

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

    for(auto &line:liberty_grid)
    {
        for(auto &liberty:line)
        {
            if(liberty.isPlaced())
                window.draw(liberty.getDrawableShape());
        }
    }
}

VisualBoard::~VisualBoard()
{
    for(auto label_ptr:intersection_numbers)
        delete label_ptr;
}