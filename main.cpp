#include "Board.h"

int main ()
{
    int cycle = 0;
    char player = 'B';
    bool is_running = true;

    std::vector<Node> nodes;

    Board board(9, nodes);
        
    std::vector<std::pair<int, int>> moves = {
        {0,0}, {0,1}, 
        {1,0}, {4,4}, 
        {2,0}, {4,5}, 
        {3,4}, {2,4}, 
        {1,4}, {0,4}, 
        {0,3}, {0,2}, 
        {0,8}, {3,0},
        {1,8}, {2,1},
        {2,8}, {1,1}
    };

    while(is_running)
    {
        std::cout << "<<===========>> Moves: " << cycle << " Player: "<< player <<" <<===========>>" << std::endl;
        std::cout << std::endl;

        int x = moves[cycle].first;
        int y = moves[cycle].second;

        //std::cout << "Board bevor move: (x: " << x << "; "<< y << ")" << std::endl;
        //board.print();
    
        if (board.add_move(moves[cycle].first, moves[cycle].second, player)) 
            std::cout << "Error: bad move" << std::endl;

        std::cout <<"Board after move: (x: " << x << "; "<< y << ")" << std::endl;
        board.print();

        board.update_groups();
        std::cout << std::endl;

        board.update_liberties();
        std::cout << "Printing lberties: " << std::endl;
        board.print_liberties();
        std::cout << std::endl;

        board.kill_check();

        if(player == 'W') player = 'B';
        else player = 'W';        
        
        cycle++;
        if (cycle == moves.size()) is_running = false;

        std::cout << "groups: " << std::endl;
        board.print_group();


        //std::cout << "is running?";
        //std::cin >> is_running;
    }
    
    std::cout << "terminated." << std::endl;
}