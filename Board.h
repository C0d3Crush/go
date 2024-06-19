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

    int* cycle;
    int move_count = 0;

    char player = 'B';


    std::vector<Node> nodes;
    std::vector<int> liberties;
    std::vector<Node*> heads;

    std::vector<std::pair<int, int>> moves;


    Node* ko;

    float komi; 
    std::string ruleset; 
    std::string result; 
    std::string black_player;
    std::string white_player; 

    // reset
    void reset_visited();
    void reset_children();
    void reset_parent();
    void reset();

    int get_index(int x, int y);
    int get_x(int index);
    int get_y(int index);
public:
    Board(int size, std::vector<Node>& vect, const std::string file_path, int* c);
    Board(int size, std::vector<Node>& vect, int* c);

    ~Board();

    // we need a draw function in the future here!

    void update(char player);
    void update_groups();
    void update_liberties();
    void update_life(char player);
    void update_heads();

    bool update_cycle();

    bool find_life(Node* head);
    int remove_stones(Node* head);

    int size();
    int width();
    int height();

    Node* get_node(int index);
    int get_liberties(int x, int y);
    int get_lib_amount(int index);
    int get_moves_size();
    bool get_up_to_date();


    std::vector<Node*> get_group(Node* head);  // this one is aperently super epic!
    //void rec_group(Node* head, std::vector<Node*> *nodes);


    int add_move(int x, int y, char player);
    
    void build_dfs(int index);

    bool dfs_life(Node* head);
    void dfs_group(Node* head, std::vector<Node*> *nodes);
    //void reset();

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
