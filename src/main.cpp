#include "logic/Board.h"
#include "ui/Sdl_renderer.h"


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

    SDLRenderer renderer;
    if (!renderer.init(WINDOW_WIDTH, WINDOW_HEIGHT))
    {
        return 1;
    }

    while (is_running)
    {
        is_running = renderer.handleEvents(board, &player);
        board->update();
        board->print();
        //board->print_heads();
        board->print_groups();
        renderer.render(board);
        
        //std::cout << "continu";
        //std::cin >> is_running;
    }

    renderer.cleanup();

    std::cout << "terminated." << std::endl;
    return 0;
}
