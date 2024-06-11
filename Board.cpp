#include "Board.h"

// Constructor
Board::Board(int size, std::vector<Node>& vect) {
    this->w = size;
    this->h = size;
    this->s = size * size;

    nodes = vect;
    nodes.resize(size * size);
    liberties.resize(size * size);

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) 
        {
            int index = get_index(j, i);
            nodes[index].set_player('.');    
            nodes[index].set_index(index);

            liberties[index] = 0;
        }
    }
}

// Destructor
Board::~Board() {}

int Board::get_index(int x, int y) {
    return (y * h) + x;
}

int Board::get_x(int index)
{
    return w / index;
}

int Board::get_y(int index)
{
    return h % index;
}

int Board::size()
{
    return s;
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

int *Board::get_lib(int index)
{
    return &liberties[index];
}

void Board::kill_check()
{

}

void Board::dfs(const int index)
{

    if (get_node(index)->get_player() == '.') return;
    if (get_node(index)->get_visited()) return;

    int x = index / w;
    int y = index % h;

    Node* node = (&nodes[index]);
    node->set_visited(true);

    // check seperaly for out of bounds
    
    //up
    if (y > 0) 
    {
        Node* node_up;
        int index_up = index - w;
        node_up = (&nodes[index_up]);

        if (node_up->get_player() == node->get_player())
        {
            node->add_child(node_up, 0);
            node_up->add_parent(node);
            dfs(index_up);
        }
    }

    //Down
    if (y < s - 1) 
    {
        Node* node_down;
        int index_down = index + w;
        node_down = (&nodes[index_down]);

        if (node_down->get_player() == node->get_player())
        {
            node->add_child(node_down, 2);
            node_down->add_parent(node);
            dfs(index_down);
        }
    }

    //Left 
    if (x > 0)
    {
        Node* node_left;
        int index_left = index - 1;
        node_left = (&nodes[index_left]);

        if (node_left->get_player() == node->get_player()) 
        {
            node->add_child(node_left, 3);
            node_left->add_parent(node);
            dfs(index_left);
        }
    }

    //Right
    if(x < s - 1)
    {
        Node* node_right;
        int index_right = index + 1;
        node_right = (&nodes[index_right]);

        if (node_right->get_player() == node->get_player())
        {
            node->add_child(node_right, 1);
            node_right->add_parent(node);
            dfs(index_right);
        }
    }
}

void Board::reset_visited()
{
    for (int i = 0; i < s; i++) 
    {
        nodes[i].set_visited(false);
    }
}

void Board::reset_children()
{
    for (int i = 0; i < s; i++) 
    {
        nodes[i].add_child(nullptr, 0);
        nodes[i].add_child(nullptr, 1);
        nodes[i].add_child(nullptr, 2);
        nodes[i].add_child(nullptr, 3);
    }
}

void Board::reset_parent()
{
    for (int i = 0; i < s; i++) 
    {
        nodes[i].add_parent(nullptr);
    }
}

void Board::print()
{
    if (s == 0) 
    {
        std::cout << "empty array" <<std::endl;
        return;
    }
    
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            char player = nodes[get_index(j ,i)].get_player();

            std::cout << player;
        }
        std::cout << std::endl;
    }
}


void Board::print_group()
{
    reset_visited();

    for(int k = 0; k < size(); k++ )
    {
        if (!(nodes[k].get_player() == '.') && !(nodes[k].get_visited()))
        {
            bool alive = false;
            std::vector<int> vect = get_group(k);

            if (vect.size() == 1) 
            {
                continue;
            }

            std::cout << "Printing " << k << "-tree, colour: " << nodes[k].get_player()<<std::endl;

            for (int l = 0; l < vect.size(); l++) 
            {
                std::cout << vect[l] << ", ";
                int liberties = *get_lib(vect[l]);
                if (liberties != 0)
                {
                    alive = true;
                }
            }
        std::cout << std::endl;
        std::cout << "Alive: "<< alive << std::endl;
        std::cout << std::endl;

        }
    }
}

std::vector<int> Board::get_group(int index)
{
    std::vector<int> vect;
    vect.push_back(index);
    nodes[index].print_children(vect);
    //reset_visited();
    return vect;
}

Node Board::at(int index)
{
    return nodes[index];
}

void Board::print_liberties()
{
    for (int i= 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            std::cout << liberties[get_index(j, i)];
        }
    std::cout << std::endl;
    }
}

void Board::update_groups()
{
    reset_children();
    reset_parent();

        for (int i = 0; i < size(); i++)
        {
            reset_visited();
            dfs(i);
        }
}

void Board::update_liberties()
{
    for(int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int index = get_index(j, i);
            liberties[index] = get_liberties(j, i);
        }
    }
}
