#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "Node.h"

class Board {
private:
    int w, h;
    int s;
    std::vector<Node> nodes;
    std::vector<int> liberties;

    float komi; 
    std::string ruleset; 
    std::string result; 
    std::string black_player;
    std::string white_player; 

public:
    // Constructor and Destructor
    Board(int size, std::vector<Node>& vect);
    ~Board();

    // Member functions
    std::vector<std::pair<int, int>> parseSGF(const std::string& filePath);
    int get_index(int x, int y);
    int get_x(int index);
    int get_y(int index);
    int size();
    Node* get_node(int index);
    int get_liberties(int x, int y);
    int* get_lib(int index);

    int add_move(int x, int y, char player);
    //void init_board();

    void kill_check();
    
    void dfs(int index);

    void reset_visited();
    void reset_children();
    void reset_parent();

    void update_groups();
    void update_liberties();

    // Testin functions
    void print_group();
    void print();
    std::vector<int> get_group(int index);
    Node at(int index);
    void print_liberties();
};

#endif // GAME_H
