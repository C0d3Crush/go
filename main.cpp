#include "Board.h"

#include <SDL2/SDL.h>
#include <cmath>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int BOARD_MARGIN = 30;

int main (int argc, char** argv)
{
    int cycle = 0;
    int move_count = 0;
    char player = 'B';
    bool is_running = true;

    std::vector<Node> nodes;
    std::vector<Board> boards;
    
    if (argc == 1 )
    {
        std::cout << "empty board:" << std::endl;
        boards.push_back(Board(9, nodes));
    }
    /*else if (argc == 2)
    {
        std::cout << "filled board:" << std::endl;
        boards.push_back(Board(9, nodes, argv[1]));
    }*/
   else 
   {

   }

    Board* board = &boards[0];

    while(board->update())
    {
        //board->draw();
    }

    board->print();

    
    std::cout << "terminated." << std::endl;

    return 0;
}