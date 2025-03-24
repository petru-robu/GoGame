#include "../inc/backend_board.h"

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

/*Intersection*/
Intersection::Intersection(GameContext& ctx, std::pair<int, int> coords, CellType type): 
ctx(ctx), coords(coords), type(type)
{
    group = nullptr;
}

/* setters and getters */
void Intersection::setType(CellType t)
{
    type = t;
}
CellType Intersection::getType()
{
    return type;
}

void Intersection::setGroup(Group* g)
{
    group = g;
}
Group* Intersection::getGroup()
{
    return group;
}

std::pair<int,int> Intersection::getCoords()
{
    return coords;
}

/*Group*/

Group::Group(){}

std::set<Intersection*>& Group::get_stones()
{
    return stones;
}
std::set<Intersection*>& Group::get_liberties()
{
    return liberties;
}
void Group::addStone(Intersection* inter)
{
    stones.insert(inter);
    inter->setGroup(this);
}

void Group::addLiberty(Intersection* inter)
{   
    liberties.insert(inter);
    inter->setGroup(this);
}
void Group::removeLiberty(Intersection* inter)
{
    liberties.erase(inter);
    inter->setGroup(nullptr);
    inter->setType(CellType::EMPTY);
}

void Group::free()
{
    for(auto inter : stones)
    {
        inter->setType(CellType::EMPTY);
        inter->setGroup(nullptr);
    }
}

void Group::extend(Group* to_append)
{
    auto to_append_stones = to_append->get_stones();
    auto to_append_liberties = to_append->get_liberties();

    for(auto inter:to_append_stones)
        addStone(inter);

    for(auto inter:to_append_liberties)
        addLiberty(inter);
}


/*board*/
BackendBoard::BackendBoard(GameContext& ctx): ctx(ctx)
{
    int gs = ctx.getGameSize();
    for(int i=0; i<gs; i++)
    {
        std::vector<Intersection> line;
        for(int j=0; j<gs; j++)
        {
            line.push_back(Intersection(ctx, {i, j}, CellType::EMPTY));
        }
        board_matrix.push_back(line);
    }
}

void BackendBoard::calculate_liberties(Group* group)
{
    int gs = ctx.getGameSize();

    std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for(auto inter : group->get_stones())
    {  
        for(auto const &dir: directions)
        {
            int new_cx = inter->getCoords().first + dir.first, new_cy = inter->getCoords().second + dir.second;
            if(new_cx < 0 || new_cy < 0 || new_cx >= gs || new_cy >= gs)
                continue;

            Intersection* new_inter = &board_matrix[new_cx][new_cy];

            if(new_inter->getType() == CellType::EMPTY)
            {
                if(inter->getType() == CellType::WHITE)
                {
                    new_inter->setType(CellType::WHITE_LIBERTY);
                }   
                else if(inter->getType() == CellType::BLACK)
                {
                    new_inter->setType(CellType::BLACK_LIBERTY);
                }

                group->addLiberty(new_inter);
            }
        }   
    }
}

void BackendBoard::calculate_liberties(Intersection* inter)
{
    int gs = ctx.getGameSize();
    std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for(auto const &dir: directions)
    {
        int new_cx = inter->getCoords().first + dir.first, new_cy = inter->getCoords().second + dir.second;
        if(new_cx < 0 || new_cy < 0 || new_cx >= gs || new_cy >= gs)
            continue;

        Intersection* new_inter = &board_matrix[new_cx][new_cy];

        if(new_inter->getType() == CellType::EMPTY)
        {
            if(inter->getType() == CellType::WHITE)
            {
                new_inter->setType(CellType::WHITE_LIBERTY);
            }   
            else if(inter->getType() == CellType::BLACK)
            {
                new_inter->setType(CellType::BLACK_LIBERTY);
            }

            Group* group = inter->getGroup();
            group->addLiberty(new_inter);
        }
    } 
}

void BackendBoard::merge_groups(Intersection* curr_stone)
{
    int gs = ctx.getGameSize();
    std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for(auto const &dir: directions)
    {
        int new_cx = curr_stone->getCoords().first + dir.first, new_cy = curr_stone->getCoords().second + dir.second;
        if(new_cx < 0 || new_cy < 0 || new_cx >= gs || new_cy >= gs)
            continue;

        Intersection* new_inter = &board_matrix[new_cx][new_cy];

        if((new_inter->getType() == CellType::BLACK || new_inter->getType() == CellType::WHITE)
            && new_inter->getType() == curr_stone->getType())
        {
            CellType type = new_inter->getType();
            Group* curr_group = curr_stone->getGroup();
            Group* new_group = new_inter->getGroup();

            if(curr_group != new_group)
            {
                curr_group->extend(new_group);
            
                if(type == CellType::BLACK)
                    black_groups.erase(new_group);
                else
                    white_groups.erase(new_group);
                delete new_group;
            }
            
        }
    }
}

void BackendBoard::addStone(int cx, int cy, CellType cell_type)
{
    Intersection* curr_inter = &board_matrix[cx][cy];
    CellType initial_type = curr_inter->getType();

    if(initial_type == CellType::WHITE || initial_type == CellType::BLACK)
    {
        std::cout<<"Cannot place stone here! Space taken!";
        return;
    }

    bool capture = false;

    if(initial_type == CellType::WHITE_LIBERTY || initial_type == CellType::BLACK_LIBERTY)
    {
        //we are placing on liberty
        Group* group_of_liberty = curr_inter->getGroup();
        group_of_liberty->removeLiberty(curr_inter);

        std::cout<<"Placing on "<<initial_type<<' '<<group_of_liberty->get_liberties().size()<<'\n';

        if(group_of_liberty->get_liberties().size() == 0)
        {   
            capture = true;
            group_of_liberty->free();

            white_groups.erase(group_of_liberty);
            black_groups.erase(group_of_liberty);
            
            delete group_of_liberty;
        }
    }

    curr_inter->setType(cell_type);
    Group* newGroup = new Group();
    newGroup->addStone(curr_inter);

    if(cell_type == CellType::BLACK)
        black_groups.insert(newGroup);

    if(cell_type == CellType::WHITE)
        white_groups.insert(newGroup);

    calculate_liberties(curr_inter);
    merge_groups(curr_inter);

    if(capture)
    {
        calculate_liberties(curr_inter->getGroup());
    }

    /*Print backend_board for debugging.*/
    std::cout<<"The backend board is: \n"<<*this<<'\n';
}

const std::vector<std::vector<Intersection>>& BackendBoard::getBoardMatrix()
{
    return board_matrix;
}

std::ostream& operator<<(std::ostream& os, BackendBoard& backend_board)
{   
    int idx = 1;
    for(auto &grp:backend_board.white_groups)
    {
        os<<"Group W"<<idx<<": ";

        for(auto inter : grp->get_stones())
        {
            os<<'('<<inter->getCoords().first<<',';
            os<<inter->getCoords().second<<") ";
        }
        os<<'\n';
        idx++;
    }

    idx = 1;
    for(auto &grp:backend_board.black_groups)
    {
        os<<"Group B"<<idx<<": ";

        for(auto inter : grp->get_stones())
        {
            os<<'('<<inter->getCoords().first<<',';
            os<<inter->getCoords().second<<") ";
        }
        os<<'\n';
        idx++;
    }


    int game_size = backend_board.ctx.getGameSize();
    std::vector<std::vector<Intersection>> board_matrix = backend_board.getBoardMatrix();
    for(int i=0; i<game_size; i++)
    {
        for(int j=0; j<game_size; j++)
        {
            if(board_matrix[i][j].getType() == CellType::WHITE)
                os<<"W";
            else if(board_matrix[i][j].getType() == CellType::BLACK)
                os<<"B";
            else
                os<<"_";
        }
        os<<"\n";
    }

    return os;


}

BackendBoard::~BackendBoard()
{   
    for(auto el: white_groups)
        delete el;

    for(auto el: black_groups)
        delete el;
}