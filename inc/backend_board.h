#ifndef BACKEND_BOARD_H
#define BACKEND_BOARD_H

#include <vector>
#include <set>
#include <iostream>

#include "group.h"

class BackendBoard
{
private:
    GameContext& ctx;
    std::vector<std::vector<Intersection>> board_matrix;

    std::set<Group*> white_groups;
    std::set<Group*> black_groups;

    void update_liberties(Group* group);
    void capture(Group* group);

public:
    explicit BackendBoard(GameContext& ctx);

    void addStone(int cx, int cy, CellType type);
    const std::vector<std::vector<Intersection>>& getBoardMatrix() const;

    ~BackendBoard();
};


#endif