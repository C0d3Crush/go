#include "Node.h"

void Node::add_child(Node *child, int direction)
{
    switch (direction)
    {
    case 0:
        children.up = child;
        break;

    case 1: 
        children.right = child;
        break;

    case 2:
        children.down = child;
        break;

    case 3:    
        children.left = child;
        break;
    default:
        break;
    }
}

void Node::add_parent(Node *parent)
{
    this->parent = parent;
}

void Node::print_children(std::vector <int>& vect)
{
    visited = true;

    if(!(children.up == nullptr))
    {
        if (!(children.up->get_visited())) 
        {
            //std::cout << "child up: " << children.up->get_index();
            vect.push_back(children.up->get_index());
            children.up->print_children(vect);
        }
    }
    
    if(!(children.right == nullptr))
    {
        if (!(children.right->get_visited()))
        {
            //std::cout << "child right: " << children.right->get_index() << std::endl;
            vect.push_back(children.right->get_index());
            children.right->print_children(vect);
        }
    }
    
    if(!(children.down == nullptr))
    {
        if (!(children.down->get_visited()))
        {
            //std::cout << "child down: " << children.down->get_index() << std::endl;
            vect.push_back(children.down->get_index());
            children.down->print_children(vect);
        }
    }
    
    if(!(children.left == nullptr))
    {
        if (!(children.left->get_visited()))
        {
            //std::cout << "child left: " << children.left->get_index() << std::endl;
            vect.push_back(children.left->get_index());
            children.left->print_children(vect);    
        }
    }
}

Node* Node::get_child(int direction)
{
    switch (direction)
    {
    case 0:
        return children.up;
        break;

    case 1: 
        return children.right;
        break;

    case 2:
        return children.down;
        break;

    case 3:    
        return children.left;
        break;
    default:
        break;
    }
}

Node *Node::get_parent()
{
    return parent;
}

// Default constructor
Node::Node() : player('.') 
{
    parent = nullptr;
    visited = false;
}

// Constructor with a char parameter
Node::Node(char value) : player(value) 
{
    parent = nullptr;
    visited = false;
}

// Copy constructor
Node::Node(const Node& other) : player(other.player), visited(other.visited) {}

// Assignment operator
Node& Node::operator=(const Node& other) {
    if (this != &other) { // Check for self-assignment
        player = other.player;
        visited = other.visited;
    }
    return *this;
}

// Destructor
Node::~Node() {}

// Getter for player
char Node::get_player() const {
    return player;
}

// Setter for player
void Node::set_player(char value) {
    player = value;
}

int Node::get_index()
{
    return index;
}

void Node::set_index(int i)
{
    index = i;
}

bool Node::get_visited() const
{
    return visited;
}

void Node::set_visited(bool value)
{
    visited = value;
}

/*
bool Node::is_head() const
{
    return head;
}

*/
