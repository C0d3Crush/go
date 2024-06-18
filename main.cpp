#include "Board.h"

int main (int argc, char** argv)
{
    
    bool is_running = true;

    std::vector<Node> nodes;

    int cycle = -1;

    if (argc == 2)
    {
        cycle = atoi(argv[1]);
    }

    Board board(9, nodes, "../data/sample.sgf", cycle);

    while(board.update_move())
    {
        
    }
    
    std::cout << "terminated." << std::endl;

    return 0;
}