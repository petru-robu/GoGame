#include "../inc/backend_board.h"

// BackendPiece::BackendPiece(GameContext& ctx, int cx=0, int cy=0, int type=0): 
// ctx(ctx), coords({cx, cy}), type(type)
// {}

// bool operator<(const BackendPiece& p1, const BackendPiece& p2)
// {
//     int gs = p1.ctx.getGameSize();
//     return p1.coords.first*gs + p1.coords.second < p2.coords.first*gs + p2.coords.second;
// }

// bool operator==(const BackendPiece& p1, const BackendPiece& p2)
// {
//     return (p1.coords == p2.coords && p1.type == p2.type);
// }

// bool operator!=(const BackendPiece& p1, const BackendPiece& p2)
// {
//     return !(p1 == p2);
// }

// BackendPiece& BackendPiece::operator=(const BackendPiece& bp)
// {   
//     ctx = bp.ctx;
//     coords = bp.coords;
//     type = bp.type;

//     return *this;
// }

/*enum stdout*/
std::ostream& operator<<(std::ostream& os, CellType& cell_type)
{
    if(cell_type == CellType::WHITE)
        os<<"White";
    else if(cell_type == CellType::BLACK)
        os<<"Black";
    else if(cell_type == CellType::WHITE_LIBERTY)
        os<<"White Liberty";
    else if(cell_type == CellType::BLACK_LIBERTY)
        os<<"Black Liberty";
    else if(cell_type == CellType::EMPTY)
        os<<"Empty";
    return os;
}


/*board*/
BackendBoard::BackendBoard(GameContext& ctx): ctx(ctx)
{
    int gs = ctx.getGameSize();

    for(int i=0; i<gs; i++)
    {
        std::vector<CellType> line(gs, CellType::EMPTY);
        board_matrix.push_back(line);
    }
}

void BackendBoard::addStone(int cx, int cy, CellType cell_type)
{
    board_matrix[cx][cy] = cell_type;
    std::cout<<cell_type<<" stone placed at: "<<cx<<' '<<cy<<'\n';
}

const std::vector<std::vector<CellType>>& BackendBoard::getBoardMatrix()
{
    return board_matrix;
}

std::ostream& operator<<(std::ostream& os, BackendBoard& backend_board)
{
    int game_size = backend_board.ctx.getGameSize();
    std::vector<std::vector<CellType>> board_matrix = backend_board.getBoardMatrix();
    for(int i=0; i<game_size; i++)
    {
        for(int j=0; j<game_size; j++)
        {
            if(board_matrix[i][j] == CellType::WHITE)
                os<<"W";
            else if(board_matrix[i][j] == CellType::BLACK)
                os<<"B";
            else if(board_matrix[i][j] == CellType::EMPTY)
                os<<"_";
        }
        os<<"\n";
    }

    return os;
}