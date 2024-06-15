#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>

#include "Node.h"

class Board {
private:
    int w, h;
    int s;
    std::vector<Node> nodes;
    std::vector<Node*> heads;

    float komi; 
    std::string ruleset; 
    std::string result; 
    std::string black_player;
    std::string white_player; 

public:
    Board(int size, std::vector<Node>& vect);
    ~Board();

    // we need a draw function in the future here!

    void update();
    void update_groups();
    void update_liberties();
    void update_life();

    bool find_life(Node* head);
    void remove_stones(Node* head);

    int get_index(int x, int y);
    int get_x(int index);
    int get_y(int index);
    int size();
    Node* get_node(int index);
    int get_liberties(int x, int y);
    int* get_lib(int index);

    std::vector<Node*> get_group(Node* head);  // this one is aperently super epic!
    void rec_group(Node* head, std::vector<Node*> *nodes);


    int add_move(int x, int y, char player);
    
    void dfs(int index);

    // reset
    void reset_visited();
    void reset_children();
    void reset_parent();
    void reset();

    // print
    void update_heads();
    void print();
    void print_heads();
    void print_groups();
    void print_coords(int index);
};

#endif // GAME_H
