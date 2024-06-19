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

    Board board(9, nodes, &cycle);

    while(is_running)
    {
        is_running = board.update();
        board.print();
    }
    
    std::cout << "terminated." << std::endl;

    return 0;
}