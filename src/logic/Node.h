#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <queue>



class Node {
public:
    struct Children
    {
        Node* up = nullptr;
        Node* right = nullptr;
        Node* down = nullptr;
        Node* left = nullptr;
    };

    // Constructors
    Node();
    Node(char value);

    // Copy constructor
    Node(const Node& other);

    // Assignment operator
    Node& operator=(const Node& other);

    // Destructor
    ~Node();

    // Getter and Setter for player
    char get_player() const;
    int get_index();
    bool get_visited() const;
    //bool is_head() const;
    Node* get_child(int direction);
    Node* get_parent();
    int get_liberties();
    int get_children_size();

    void set_index(int i);   
    void set_player(char value);
    void set_visited(bool value);
    void add_child(Node* child, int pos);
    void add_parent(Node* parent);
    void set_liberties(int l);

    // Getter methods for accessing children
    Node* getUpChild() const { return children.up; }
    Node* getRightChild() const { return children.right; }
    Node* getDownChild() const { return children.down; }
    Node* getLeftChild() const { return children.left; }

    // for testing 
    void print_children(std::vector<int>& vect);

    // Print tree method
    void print_tree(int depth = 0) const;


private:
    char player;
    //std::vector<std::shared_ptr<Node>> children;

    Node* parent;
    //std::vector<Node*> children;
    //std::tuple<Node*, Node*, Node*, Node*> children;
    Children children;
    bool visited;
    int index;
    int liberties;

    void print_indent(int depth) const;

};

#endif // MOVE_H
