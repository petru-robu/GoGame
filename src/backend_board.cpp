#include "../inc/backend_board.h"

BackendPiece::BackendPiece(GameContext& ctx, int cx=0, int cy=0, int type=0): 
ctx(ctx), coords({cx, cy}), type(type)
{

}

bool operator<(const BackendPiece& p1, const BackendPiece& p2)
{
    int gs = p1.ctx.getGameSize();
    return p1.coords.first*gs + p1.coords.second < p2.coords.first*gs + p2.coords.second;
}

bool operator==(const BackendPiece& p1, const BackendPiece& p2)
{
    return (p1.coords == p2.coords && p1.type == p2.type);
}

bool operator!=(const BackendPiece& p1, const BackendPiece& p2)
{
    return !(p1 == p2);
}

BackendPiece& BackendPiece::operator=(const BackendPiece& bp)
{   
    ctx = bp.ctx;
    coords = bp.coords;
    type = bp.type;

    return *this;
}

/*board*/
BackendBoard::BackendBoard(GameContext& ctx): ctx(ctx)
{
    int gs = ctx.getGameSize();

    for(int i=0; i<gs; i++)
    {
        std::vector<int> line(gs, -1);
        board_matrix.push_back(line);
    }
}

void BackendBoard::addStone(int cx, int cy, int type)
{
    std::cout<<cx<<' '<<cy<<'\n';
    board_matrix[cx][cy] = type;
}

const std::vector<std::vector<int>>& BackendBoard::getBoardMatrix()
{
    return board_matrix;
}

