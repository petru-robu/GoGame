#ifndef BACKEND_BOARD_H
#define BACKEND_BOARD_H

#include <vector>
#include <iostream>
#include <set>
#include <map>
#include "game_context.h"

// class BackendPiece
// {
//     private:
//         GameContext& ctx;
//         std::pair<int, int> coords;
//         int type;
    
//     public:
//         BackendPiece(GameContext& ctx, int cx, int cy, int type);

//         friend bool operator<(const BackendPiece& p1, const BackendPiece& p2);
//         friend bool operator==(const BackendPiece& p1, const BackendPiece& p2);
//         friend bool operator!=(const BackendPiece& p1, const BackendPiece& p2);

//         BackendPiece& operator=(const BackendPiece& bp);
// };

enum class CellType
{
    WHITE,
    BLACK,
    WHITE_LIBERTY,
    BLACK_LIBERTY,
    EMPTY
};
std::ostream& operator<<(std::ostream& os, CellType& cell_type);

class BackendBoard
{
private:
    GameContext& ctx;
    std::vector<std::vector<CellType>> board_matrix;

public:
    explicit BackendBoard(GameContext& ctx);

    void addStone(int cx, int cy, CellType cell_type);
    const std::vector<std::vector<CellType>>& getBoardMatrix();
    
    friend std::ostream& operator<<(std::ostream& os, BackendBoard& backend_board);

};


#endif