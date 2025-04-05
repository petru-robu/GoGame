#ifndef BACKEND_BOARD_H
#define BACKEND_BOARD_H

#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include "game_context.h"

enum class CellType
{
    WHITE,
    BLACK,
    LIBERTY,
    EMPTY
};

std::ostream& operator<<(std::ostream& os, CellType& cell_type);

class Group;

class Intersection
{
private:
    std::pair<int, int> coords;
    CellType type;
    std::set<Group*> groups;

public:
    explicit Intersection(std::pair<int, int> coords, CellType type);

    void setType(CellType type);
    CellType getType();

    void addGroup(Group* group);
    void removeGroup(Group* group);
    const std::set<Group*>& getGroups() const;

    std::pair<int, int> getCoords();
};  

class Group
{
private:
    CellType group_type;

    std::set<Intersection*> stones;
    std::set<Intersection*> liberties;

public:
    Group();

    const std::set<Intersection*>& get_stones() const;
    const std::set<Intersection*>& get_liberties() const;

    void addStone(Intersection* inter);
    
    void addLiberty(Intersection* inter);
    void removeLiberty(Intersection* inter);

    void setGroupType(CellType grp_type);
    CellType getGroupType();

    void extend(Group* group);
};

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
    
    friend std::ostream& operator<<(std::ostream& os, BackendBoard& backend_board);

    ~BackendBoard();

};


#endif