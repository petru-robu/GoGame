#include "../inc/group.h"

/*enum stdout*/
std::ostream& operator<<(std::ostream& os, CellType& cell_type)
{
    if(cell_type == CellType::WHITE)
        os<<"White";
    else if(cell_type == CellType::BLACK)
        os<<"Black";
    else if(cell_type == CellType::LIBERTY)
        os<<"White/Black Liberty";
    else if(cell_type == CellType::EMPTY)
        os<<"Empty";
    return os;
}

/*Intersection*/
Intersection::Intersection(std::pair<int, int> coords, CellType type): 
coords(coords), type(type)
{}

/*Intersection setters and getters */
void Intersection::setType(CellType t)
{
    type = t;
}
CellType Intersection::getType()
{
    return type;
}

void Intersection::addGroup(Group* g)
{
    groups.insert(g);
}
void Intersection::removeGroup(Group* g)
{
    groups.erase(g);
}
const std::set<Group*>& Intersection::getGroups() const
{
    return groups;
}

std::pair<int,int> Intersection::getCoords()
{
    return coords;
}

/*Group*/
Group::Group():group_type(CellType::EMPTY)
{}

const std::set<Intersection*>& Group::get_stones() const
{
    return stones;
}
const std::set<Intersection*>& Group::get_liberties() const
{
    return liberties;
}

void Group::setGroupType(CellType grp_type)
{
    group_type = grp_type;
}

CellType Group::getGroupType()
{
    return group_type;
}


void Group::addStone(Intersection* inter)
{
    stones.insert(inter);
    inter->addGroup(this);
}

void Group::addLiberty(Intersection* inter)
{   
    liberties.insert(inter);
    inter->addGroup(this);
}
void Group::removeLiberty(Intersection* inter)
{
    liberties.erase(inter);
    inter->removeGroup(this);
}

void Group::extend(const Group* to_append)
{
    auto to_append_stones = to_append->get_stones();
    auto to_append_liberties = to_append->get_liberties();

    for(auto inter:to_append_stones)
        addStone(inter);

    for(auto inter:to_append_liberties)
        addLiberty(inter);
}