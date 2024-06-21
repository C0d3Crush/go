#include "logic/Board.h"

const int WINDOW_WIDTH = 600;       
const int WINDOW_HEIGHT = 600;
const int BOARD_MARGIN = 30;


int main (int argc, char** argv)
{
    int cycle = 0;
    char player = 'B';
    bool is_running = true;
    std::vector<Node> nodes;
    std::vector<Board> boards;

    if (argc == 1)
    {
        std::cout << "empty board:" << std::endl;
        boards.push_back(Board(9, nodes));
    }
    else if (argc == 2)
    {
        std::cout << "loaded board:" << std::endl;
        boards.push_back(Board(9, nodes, argv[1]));
    }
    else
    {
        std::cerr << "Usage: " << argv[0] << "\n";
        return 1;
    }

    Board* board = &boards[0];

    while (board->update())
    {
        board->print();
    }

    std::cout << "terminated." << std::endl;
    return 0;
}
