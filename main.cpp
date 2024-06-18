#include "Board.h"

int main (int argc, char** argv)
{
    int cycle = 0;
    int move_count = 0;
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
        {2,8}, {1,1},
        {4,8}, {8,1}
    };

    if (argc == 0)
    {
        cycle = moves.size();
    }
    else if (argc == 1)
    {
        cycle = atoi(argv[1]);
    }

    std::cout<< "checkout move: "<< cycle << std::endl;        

    while(is_running)
    {
        if (move_count < cycle)
        {
            int x = moves[move_count].first;
            int y = moves[move_count].second;    
        
            if (board.add_move(moves[move_count].first, moves[move_count].second, player)) 
            {
                //std::cerr << "Error: bad move" << std::endl;
            }
            else
            {
                if(player == 'W') player = 'B';
                else player = 'W';    
            }

            board.update(player);     
            move_count++;
        }
        else if (cycle < move_count)
        {
            board.reset();
            player = 'B';

            for (move_count = 0; move_count < cycle; move_count++)
            {
                int x = moves[move_count].first;
                int y = moves[move_count].second;    
            
                if (board.add_move(moves[move_count].first, moves[move_count].second, player)) 
                {
                    std::cerr << "Error: bad move" << std::endl;
                }
                else
                {
                    if(player == 'W') player = 'B';
                    else player = 'W';    
                }
                board.update(player);     
            }
        }

        //board.print();
        //board.print_liberties();
        //board.print_groups();
        //board.print_heads();  
    }
    
    std::cout << "terminated." << std::endl;

    return 0;
}