#include "Board.h"

int main ()
{
    int cycle = 0;
    char player = 'B';
    bool is_running = true;

    std::vector<Node> nodes;

    Board board(9, nodes);

    std::vector<std::pair<int, int>> moves = board.parseSGF("../data/sample.sgf");


    while(is_running)
    {
        std::cout << "<<===========>> Moves: " << cycle << " Player: "<< player <<" <<===========>>" << std::endl;
        std::cout << std::endl;

        int x = moves[cycle].first;
        int y = moves[cycle].second;    
    
        if (board.add_move(moves[cycle].first, moves[cycle].second, player)) std::cerr << "Error: bad move" << std::endl;

        std::cout << "move: ("<< x << "; " << y << ")" << std::endl;

        board.update();     

        board.print();
        //board.print_liberties();
        //board.print_groups();
        //board.print_heads();  

        if(player == 'W') player = 'B';     //change colour for next move/cycle
        else player = 'W';           

        cycle++;    // increment game cycle
        if (cycle == moves.size()) is_running = false;

   
    }
    
    std::cout << "terminated." << std::endl;
}