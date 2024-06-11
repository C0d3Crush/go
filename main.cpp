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
        int y = moves[cycle].second;    //making x and y 
    
        if (board.add_move(moves[cycle].first, moves[cycle].second, player)) // setting x and y to board and checking legality
            std::cerr << "Error: bad move" << std::endl;

        std::cout <<"Board after move: (x: " << x << "; "<< y << ")" << std::endl;  //printing board
        board.print();
        std::cout << std::endl;

        board.update();             // this is doing all the live and death action

        std::cout << "Printing lberties: " << std::endl;    //print liberties
        board.print_liberties();
        std::cout << std::endl;

        if(player == 'W') player = 'B';     //change colour for next move/cycle
        else player = 'W';        
        
        cycle++;    // increment game cycle
        if (cycle == moves.size()) is_running = false;

        std::cout << "groups: " << std::endl;   //print groups that are found in the dfs search, test this profoundly
        board.print_group();
    }
    
    std::cout << "terminated." << std::endl;
}