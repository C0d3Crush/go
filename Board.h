#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>

#include <SDL2/SDL.h>

#include "Node.h"

class Board {
private:

    const int WINDOW_WIDTH = 600;       
    const int WINDOW_HEIGHT = 600;
    const int BOARD_MARGIN = 30;

    int w, h;
    int s;

    int cycle;
    int move_count = 0;

    char player = 'B';


    std::vector<Node> nodes;
    std::vector<Node*> heads;

    std::vector<std::pair<int, int>> moves;

    Node* ko;

    float komi; 
    std::string ruleset; 
    std::string result; 
    std::string black_player;
    std::string white_player; 

    // for drawing 
    void draw_stones(SDL_Renderer *renderer);
    void draw_square(SDL_Renderer *renderer, int centerX, int centerY, int radius);
    void draw_board(SDL_Renderer *renderer);

    // for update
    void update_cycle(char player);
    void update_groups();
    void update_liberties();
    void update_life(char player);
    void update_heads();

    // reset
    void reset_visited();
    void reset_children();
    void reset_parent();
    void reset();

    // for testing
    void print_heads();
    void print_groups();
    void print_coords(int index);

    // access function
    int size();
    int width();
    int height();

    int get_index(int x, int y);
    int get_x(int index);
    int get_y(int index);

    int get_liberties(int x, int y);

    std::vector<Node*> get_group(Node* head);  // this one is aperently super epic!
    
    int add_move(int x, int y, char player);

    // dfs operations    
    void build_dfs(int index);
    bool dfs_life(Node* head);
    void dfs_group(Node* head, std::vector<Node*> *nodes);

    bool find_life(Node* head);
    int remove_stones(Node* head);

    // file access
    std::vector<std::pair<int, int>> parseSGF(const std::string& filePath);


public:
    Board(int size, std::vector<Node>& vect, const std::string file_path);
    Board(int size, std::vector<Node>& vect);

    ~Board();

    void print();
    void draw(SDL_Renderer *renderer);

    bool update();

    bool get_up_to_date();
    int get_moves_size();

    // visual interface 
    void handle_mouse_click(const SDL_Event& e, char* player, int* cycle);

};

#endif // GAME_H
