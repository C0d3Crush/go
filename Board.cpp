#include "Board.h"

// Constructor
Board::Board(int size, std::vector<Node>& vect, const std::string file_path, int* c) 
{
    this->w = size;
    this->h = size;
    this->s = size * size;

    cycle = c;
    player = 'B';
    //moves = parseSGF(file_path);

    if (*cycle == -1) *cycle = moves.size();

    nodes = vect;
    nodes.resize(size * size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) 
        {
            int index = get_index(j, i);
            nodes[index].set_player('.');    
            nodes[index].set_index(index);
        }
    }
}

Board::Board(int size, std::vector<Node>& vect, int* c) 
{
    this->w = size;
    this->h = size;
    this->s = size * size;

    cycle = c;
    player = 'B';
    moves = {
        {0,0}, {0,1}, 
        {1,0}, {4,4}, 
        {2,0}, {4,5}, 
        {3,4}, {2,4}, 
        {1,4}, {0,4}, 
        {0,3}, {0,2}, 
        {0,8}, {3,0},
        {1,8}, {2,1},
        {2,8}, {1,1},
        {4,8}, {8,1}
    };

    if (*cycle == -1) *cycle = moves.size();

    nodes = vect;
    nodes.resize(size * size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) 
        {
            int index = get_index(j, i);
            nodes[index].set_player('.');    
            nodes[index].set_index(index);
        }
    }
}

// Destructor
Board::~Board() {}

void Board::update_cycle(char player)
{
    update_groups();
    update_liberties();
    update_heads();

    if (player == 'W') {player = 'B';}
    else {player = 'W';}

    update_life(player);

    if (player == 'W') {player = 'B';}
    else {player = 'W';}

    update_groups();
    update_liberties();
    update_heads();

    update_life (player);

}

int Board::get_index(int x, int y) {
    return (y * h) + x;
}

int Board::get_x(int index)
{
    return index % w;
}


int Board::get_y(int index)
{
    return index / h;
}


int Board::size()
{
    return s;
}

int Board::width()
{
    return w;
}

int Board::height()
{
    return h;
}

Node *Board::get_node(int index)
{
    return &nodes[index];
}

int Board::add_move(int x, int y, char player)
{
    int index = get_index(x, y);
    nodes[index].set_index(index);
    if (nodes[index].get_player() == '.')
    {
        nodes[index].set_player(player);
        return 0;
    }
    else 
    {
        return 1;
    }
}

int Board::get_liberties(int x, int y)
{
    int count = 0;
    int index = get_index(x, y);
    //up
    if (y > 0) 
    {
        if (nodes[get_index(x, y - 1)].get_player() == '.') 
            count++;
    }
    //Down
    if (y < h - 1) 
    {
        if (nodes[get_index(x, y + 1)].get_player() == '.') 
            count++;
    }

    //Left 
    if (x > 0)
    {
        if (nodes[get_index(x - 1, y)].get_player() == '.') 
            count++;
    }

    //Right
    if(x < w - 1)
    {
       if (nodes[get_index(x + 1, y)].get_player() == '.') 
        count++;
    }    
    return count;
}

int Board::get_moves_size()
{
    return moves.size();
}

bool Board::get_up_to_date()
{
    return (move_count == *cycle);
}


void Board::build_dfs(const int index)
{

    if (get_node(index)->get_player() == '.') return;
    if (get_node(index)->get_visited()) return;

    int x = index / w;
    int y = index % h;

    Node* node = (&nodes[index]);
    node->set_visited(true);

    // check seperaly for out of bounds
    
    //up
    if (y >= 0) 
    {
        Node* node_up;
        int index_up = index - w;
        node_up = (&nodes[index_up]);

        if (node_up->get_player() == node->get_player())
        {
            node->add_child(node_up, 0);
            node_up->add_parent(node);
            build_dfs(index_up);
        }
    }

    //Down
    if (y < h - 1) 
    {
        Node* node_down;
        int index_down = index + w;
        node_down = (&nodes[index_down]);

        if (node_down->get_player() == node->get_player())
        {
            node->add_child(node_down, 2);
            node_down->add_parent(node);
            build_dfs(index_down);
        }
    }

    //Left 
    if (x >= 0)
    {
        Node* node_left;
        int index_left = index - 1;
        node_left = (&nodes[index_left]);

        if (node_left->get_player() == node->get_player()) 
        {
            node->add_child(node_left, 3);
            node_left->add_parent(node);
            build_dfs(index_left);
        }
    }

    //Right
    if(x < w - 1)
    {
        Node* node_right;
        int index_right = index + 1;
        node_right = (&nodes[index_right]);

        if (node_right->get_player() == node->get_player())
        {
            node->add_child(node_right, 1);
            node_right->add_parent(node);
            build_dfs(index_right);
        }
    }
}

bool Board::dfs_life(Node *head)
{
    
    if(head->get_liberties() != 0)
    {
        return 1;
    }
    for (int i = 0; i < 4; i++)
    {
        Node* child = head->get_child(i);
        if (!(child == nullptr))
        {
            return find_life(child);
        }
    }

    return 0;
}

void Board::reset_visited()
{
    for (int i = 0; i < nodes.size(); i++) 
    {
        nodes[i].set_visited(false);
    }
}

void Board::reset_children()
{
    for (int i = 0; i < nodes.size(); i++) 
    {
        nodes[i].add_child(nullptr, 0);
        nodes[i].add_child(nullptr, 1);
        nodes[i].add_child(nullptr, 2);
        nodes[i].add_child(nullptr, 3);
    }
}

void Board::reset_parent()
{
    for (int i = 0; i < nodes.size(); i++) 
    {
        nodes[i].add_parent(nullptr);
    }
}

void Board::reset()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        nodes[i].set_player('.');
    }
}

void Board::print()
{   
    std::cout << "board" << std::endl;

    for (int i = 0; i < h; i++)
    {
        std::cout<<i;
        for (int j = 0; j < w; j++)
        {
            char player = nodes[get_index(j ,i)].get_player();

            std::cout << player;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void Board::update_heads()
{
    heads.resize(0);
    reset_visited();

    for(int k = 0; k < nodes.size(); k++ )
    {
        if (!(nodes[k].get_player() == '.') && !(nodes[k].get_visited()))
        {
            //bool alive = false;
            std::vector<Node*> vect = get_group(&nodes[k]);
            heads.push_back(&nodes[k]);
        }
    }
}

bool Board::update()
{   
    std::cout << "move_count: " << move_count << ", cycle: "<< *cycle << std::endl; 
    if (move_count < *cycle)
        {
            int x = moves[move_count].first;
            int y = moves[move_count].second;    
        
            if (add_move(moves[move_count].first, moves[move_count].second, player)) 
            {
                std::cerr << "Error: bad move" << std::endl;
            }
            else
            {
                if(player == 'W') player = 'B';
                else player = 'W';    
            }
            update_cycle(player);     
            move_count++;
            return true;
        }
        else if (*cycle < move_count)
        {
            reset();
            player = 'B';

            for (move_count = 0; move_count < *cycle; move_count++)
            {
                int x = moves[move_count].first;
                int y = moves[move_count].second;    
            
                if (add_move(moves[move_count].first, moves[move_count].second, player)) 
                {
                    std::cerr << "Error: bad move" << std::endl;
                }
                else
                {
                    if(player == 'W') player = 'B';
                    else player = 'W';    
                }
                update_cycle(player);     
            }
            return true;
        }
        if (*cycle == move_count)
        {
            return false;
        } 
}

/**
 * Prints all children of a node.
 *
 * @param node this will be viewed the head.
 * @return a vector aof all children an childrens children.
 */
std::vector<Node*> Board::get_group(Node* head)
{

    std::vector<Node*> nodes;

    reset_visited();

    dfs_group(head, &nodes);

    return nodes;
}

void Board::dfs_group(Node *head, std::vector<Node *> *nodes)
{
    if (head->get_visited()) return;

    head->set_visited(true);

    nodes->push_back(head);

    for (int i = 0; i < 4; i++)
    {
        Node* child = head->get_child(i);
        if (!(child == nullptr))
        {
            dfs_group(child, nodes);
        }
    }
}


void Board::print_heads()
{
    std::cout << "heads:"<<std::endl;
    for ( auto h : heads) 
    {
        int index = h->get_index();
        std::cout << "(" << get_x(index) << ";" << get_y(index) << ")"<< std::endl;
    }
    std::cout << std::endl;
}

void Board::print_groups()
{
    std::cout << "groups:" << std::endl;
    reset_visited();
    for(int k = 0; k < nodes.size(); k++ )
    {
        if (!(nodes[k].get_player() == '.') && !(nodes[k].get_visited()))
        {
            std::vector<Node*> vect = get_group(&nodes[k]);

            std::cout << "Printing " << "(" <<get_x(k)<< "; " << get_y(k) << ")"  << "-tree, colour: " << nodes[k].get_player()<<std::endl;

            for (int l = 0; l < vect.size(); l++) 
            {
                std::cout << "(" <<get_x(vect[l]->get_index())<< "; " << get_y(vect[l]->get_index()) << ")" << std::endl;
            }
        }
    }
}

void Board::print_coords(int index)
{

    std::cout << "coords: (" << get_x(index) << ";" << get_y(index) << ")" << std::endl; 
}

void Board::update_groups()
{
    reset_children();
    reset_parent();

        for (int i = 0; i < nodes.size(); i++)
        {
            reset_visited();
            build_dfs(i);
        }


}

void Board::update_liberties()
{
    for(int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int l = get_liberties(j, i);
            int index = get_index(j, i);
            nodes[index].set_liberties(l);
        }
    }
}



void Board::update_life(char player)
{
    for (auto head : heads)
    {

        std::vector<Node*> group = get_group(head);
        std::vector<int> liberties_update;

        bool life = false;

        for (auto e : group)
        {
            liberties_update.push_back(e->get_liberties());
        }

        for (auto e : liberties_update)
        {
            if (e == 0) continue;

            else life = true;
        }

        if (!life && head->get_player() == player) 
        {
            remove_stones(head); 
        }
    }
}

bool Board::find_life(Node *head)
{
    if (head->get_visited()) return head->get_liberties();
    
    bool value = dfs_life(head);

    reset_visited();

    return value;
}

int Board::remove_stones(Node *head)
{
    std::vector<Node*> dead_stones = get_group(head);

    for (int i = 0; i < dead_stones.size(); i++) 
    {
        //std::cout << "deleting node idx: " << i<< std::endl;
        dead_stones[i]->set_player('.'); 
    }

    return dead_stones.size();
}
