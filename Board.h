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
    std::vector<int> liberties;
    std::vector<Node*> heads;

    float komi; 
    std::string ruleset; 
    std::string result; 
    std::string black_player;
    std::string white_player; 

    // reset
    void reset_visited();
    void reset_children();
    void reset_parent();

    int get_index(int x, int y);
    int get_x(int index);
    int get_y(int index);
public:
    Board(int size, std::vector<Node>& vect);
    ~Board();

    // we need a draw function in the future here!

    void update();
    void update_groups();
    void update_liberties();
    void update_life();
    void update_heads();

    Node* get_node(int index);
    int get_liberties(int x, int y);
    int* get_lib(int index);

    int add_move(int x, int y, char player);
    
    void build_dfs(int index);

    bool dfs_life(Node* head);
    void dfs_group(Node* head, std::vector<Node*> *nodes);

    std::vector<Node*> get_group(Node* head); 
    bool find_life(Node* head);
    void remove_stones(Node* head);

    // print
    void print();
    void print_liberties();

    // file access
    std::vector<std::pair<int, int>> parseSGF(const std::string& filePath);

    void print_heads();
    void print_groups();
    void print_coords(int index);
};

#endif // GAME_H
