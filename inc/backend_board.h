#ifndef BACKEND_BOARD_H
#define BACKEND_BOARD_H

#include <vector>
#include <iostream>
#include <set>
#include <queue>
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

class Group;

class Intersection
{
private:
    GameContext& ctx;

    std::pair<int, int> coords;
    CellType type;
    Group* group;

public:
    explicit Intersection(GameContext& ctx, std::pair<int, int> coords, CellType type);


    void setType(CellType type);
    CellType getType();

    void setGroup(Group* group);
    Group* getGroup();

    std::pair<int, int> getCoords();
};  

class Group
{
private:
    std::set<Intersection*> stones;
    std::set<Intersection*> liberties;

public:
    Group();

    std::set<Intersection*>& get_stones();
    std::set<Intersection*>& get_liberties();

    void addStone(Intersection* inter);
    void removeStone(Intersection* inter);
    
    void addLiberty(Intersection* inter);
    void removeLiberty(Intersection* inter);

    void free();

    void extend(Group* group);
};

class BackendBoard
{
private:
    GameContext& ctx;
    std::vector<std::vector<Intersection>> board_matrix;

    std::set<Group*> white_groups;
    std::set<Group*> black_groups;

    void calculate_liberties(Group* group);
    void calculate_liberties(Intersection* inter);
    void merge_groups(Intersection* inter);

public:
    explicit BackendBoard(GameContext& ctx);

    void addStone(int cx, int cy, CellType type);
    const std::vector<std::vector<Intersection>>& getBoardMatrix();
    
    friend std::ostream& operator<<(std::ostream& os, BackendBoard& backend_board);

    ~BackendBoard();

};


#endif