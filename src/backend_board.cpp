#include "../inc/backend_board.h"

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
{

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

void Intersection::addGroup(Group* g)
{
    groups.insert(g);
}
void Intersection::removeGroup(Group* g)
{
    groups.erase(g);
}
std::set<Group*> Intersection::getGroups()
{
    return groups;
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
            line.push_back(Intersection({i, j}, CellType::EMPTY));
        }
        board_matrix.push_back(line);
    }
}

void BackendBoard::update_liberties(Group* group)
{
    int gs = ctx.getGameSize();
    std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for(auto inter : group->get_stones())
    {  
        for(auto const &dir: directions)
        {
            int new_cx = inter->getCoords().first + dir.first;
            int new_cy = inter->getCoords().second + dir.second;

            if(new_cx < 0 || new_cy < 0 || new_cx >= gs || new_cy >= gs)
                continue;

            Intersection* neighbour_inter = &board_matrix[new_cx][new_cy];

            if(neighbour_inter->getType() == CellType::EMPTY || neighbour_inter->getType() == CellType::LIBERTY)
            {
                // the neighbour is unocupied, it becomes liberty
                neighbour_inter->setType(CellType::LIBERTY);
                group->addLiberty(neighbour_inter);
            }
        }   
    }
}

void BackendBoard::capture(Group* captured_group)
{
    std::cout<<"Captured stone size: "<<captured_group->get_stones().size()<<"and liberties size: "<<captured_group->get_liberties().size()<<'\n';

    int gs = ctx.getGameSize();
    std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    std::set<Group*> adj_groups_to_captured;
    for(auto stone:captured_group->get_stones())
    {
        // get all the adj groups to the captured stones
        for(auto const &dir: directions)
        {
            int new_cx = stone->getCoords().first + dir.first, new_cy = stone->getCoords().second + dir.second;
            if(new_cx < 0 || new_cy < 0 || new_cx >= gs || new_cy >= gs)
                continue;

            Intersection* new_inter = &board_matrix[new_cx][new_cy];
            
            if((new_inter->getType() == CellType::WHITE && captured_group->getGroupType() == CellType::BLACK) ||
            (new_inter->getType() == CellType::BLACK && captured_group->getGroupType() == CellType::WHITE))
            {
                for(auto grp: new_inter->getGroups())
                {
                    adj_groups_to_captured.insert(grp);
                }
            }
        }
    }   
    std::cout<<adj_groups_to_captured.size()<<" no. of adj groups found!\n";
    
    for(auto captured_inter:captured_group->get_stones())
    {
        //remove the stones of the board
        captured_inter->setType(CellType::EMPTY);

        for(auto grp:captured_inter->getGroups())
            captured_inter->removeGroup(grp);
    }

    black_groups.erase(captured_group);
    white_groups.erase(captured_group);
        
    delete captured_group;
    
    //for every adj group, recalculate the liberties
    for(auto adj_group: adj_groups_to_captured)
        update_liberties(adj_group);
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
    else if(initial_type == CellType::LIBERTY)
    {
        //we are placing on liberty
        int gs = ctx.getGameSize();
        std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        std::set<Group*> groups_of_covered_liberty = curr_inter->getGroups();    

        //remove the liberty that is covered from the rest of the groups
        for(auto grp:groups_of_covered_liberty)
        {
            curr_inter->removeGroup(grp);
            grp->removeLiberty(curr_inter);
        }
        
        int enemy_capture_cnt = 0;
        bool friendlyGroupAlive = false, hasFriendlyGroup = false;

        //get the enemy groups from the groups that liberty pointed to
        std::set<Group*> enemy_groups;
        for(auto referred_group:groups_of_covered_liberty)
        {
            CellType type_of_referred_group = referred_group->getGroupType();
            if((type_of_referred_group == CellType::WHITE && cell_type == CellType::BLACK)||
                (type_of_referred_group == CellType::BLACK && cell_type == CellType::WHITE))
            {
                enemy_groups.insert(referred_group);
                if(referred_group->get_liberties().size() == 0)
                    enemy_capture_cnt += 1;
            }
            if((type_of_referred_group == CellType::WHITE && cell_type == CellType::WHITE)||
                (type_of_referred_group == CellType::BLACK && cell_type == CellType::BLACK))
            {
                hasFriendlyGroup = true;

                if(referred_group->get_liberties().size() != 0)
                    friendlyGroupAlive = true;
            }   
        }  

        //do not allow suicide
        if(hasFriendlyGroup && !friendlyGroupAlive && enemy_capture_cnt == 0)
        {
            //This move is suicide (do not allow)
            std::cout<<"Suicide!\n";

            //revert changes
            for(auto grp:groups_of_covered_liberty)
                grp->addLiberty(curr_inter);
            return;
        }

        //get the friendly adjacent groups
        std::set<Group*> to_merge_with;
        for(auto const &dir: directions)
        {
            int new_cx = curr_inter->getCoords().first + dir.first, new_cy = curr_inter->getCoords().second + dir.second;
            if(new_cx < 0 || new_cy < 0 || new_cx >= gs || new_cy >= gs)
                continue;

            Intersection* new_inter = &board_matrix[new_cx][new_cy];
            if(new_inter->getType() == cell_type)
            {       
                for(auto grp:new_inter->getGroups())
                    to_merge_with.insert(grp);
            }
        }
        
        //create the new group
        Group* newGroup = new Group();
        newGroup->addStone(curr_inter);
        newGroup->setGroupType(cell_type);
        curr_inter->setType(cell_type);

        if(cell_type == CellType::BLACK)
        {
            black_groups.insert(newGroup);
        }   
        else if(cell_type == CellType::WHITE)
        {
            white_groups.insert(newGroup);
        }
        update_liberties(newGroup);

        //check if move is suicide
        if(newGroup->get_liberties().size() == 0)
        {
            int cx = curr_inter->getCoords().first;
            int cy = curr_inter->getCoords().second;
            CellType eye_type;

            //if there is 0 out of maximum 4 liberties, stone is in an eye
            //get the eye's type
            for(auto dir:directions)
            {
                int new_cx = cx + dir.first;
                int new_cy = cy + dir.second;

                if(new_cx < 0 || new_cy < 0 || new_cx >= gs || new_cy >= gs)
                    continue;
                
                Intersection* adj = &board_matrix[new_cx][new_cy];
                eye_type = adj->getType();
            }

            if(eye_type != cell_type && enemy_capture_cnt == 0) 
            {
                //This move is suicide (do not allow)
                std::cout<<"Suicide!\n";

                //revert changes
                curr_inter->setType(CellType::LIBERTY);
                black_groups.erase(newGroup);
                white_groups.erase(newGroup);
                delete newGroup;
                for(auto grp:groups_of_covered_liberty)
                    grp->addLiberty(curr_inter);

                return;
            }
        }
        
        //managing of merges
        if(!to_merge_with.empty())
        {
            std::cout<<"Merging with "<<to_merge_with.size()<<" groups!\n";

            for(auto group_to_merge:to_merge_with)
            {   
                newGroup->extend(group_to_merge);

                for(auto liberty:group_to_merge->get_liberties())
                {
                    liberty->removeGroup(group_to_merge);
                }
                for(auto stone:group_to_merge->get_stones())
                {
                    stone->removeGroup(group_to_merge);
                }

                if(cell_type == CellType::BLACK)
                {
                    black_groups.erase(group_to_merge);
                }
                else if(cell_type == CellType::WHITE)
                {
                    white_groups.erase(group_to_merge);
                }
                delete group_to_merge;
            }
        }

        //managing of captures
        for(auto enemy:enemy_groups)
        {
            if(enemy->get_liberties().size() == 0)
            {
                capture(enemy);
            }
        }
    }
    else if(initial_type == CellType::EMPTY)
    {
        curr_inter->setType(cell_type);

        Group* newGroup = new Group();
        newGroup->setGroupType(cell_type);
        newGroup->addStone(curr_inter);

        update_liberties(newGroup);

        if(cell_type == CellType::BLACK)
        {
            black_groups.insert(newGroup);
        }
        else if(cell_type == CellType::WHITE)
        {
            white_groups.insert(newGroup);
        }
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
            os<<'('<<inter->getCoords().second + 1<<',';
            os<<inter->getCoords().first + 1<<") ";
        }

        os<<"Liberty count: "<<grp->get_liberties().size();
        os<<'\n';
        idx++;

    }

    idx = 1;
    for(auto &grp:backend_board.black_groups)
    {
        os<<"Group B"<<idx<<": ";

        for(auto inter : grp->get_stones())
        {
            os<<'('<<inter->getCoords().second + 1<<',';
            os<<inter->getCoords().first + 1<<") ";
        }
        os<<"Liberty count: "<<grp->get_liberties().size();
        os<<'\n';
        idx++;
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