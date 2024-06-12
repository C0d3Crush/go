#include "Board.h"

#include <SDL2/SDL.h>
#include <cmath>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int BOARD_MARGIN = 30;

void drawBoard(SDL_Renderer* renderer, int size) 
{
    int boardSize = sqrt(size);
    int cellSize = (WINDOW_WIDTH - 2 * BOARD_MARGIN) / (boardSize - 1);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    for (int i = 0; i < boardSize; ++i) 
    {
        SDL_RenderDrawLine
        (
            renderer, 
            BOARD_MARGIN, 
            BOARD_MARGIN + i * cellSize, 
            WINDOW_WIDTH - BOARD_MARGIN, 
            BOARD_MARGIN + i * cellSize
        );
        SDL_RenderDrawLine
        (
            renderer, 
            BOARD_MARGIN + i * cellSize, 
            BOARD_MARGIN, 
            BOARD_MARGIN + i * cellSize, 
            WINDOW_HEIGHT - BOARD_MARGIN
        );
    }
}

void drawSquare(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    int squareSize = radius * 2; // Square size is double the radius

    // Calculate the coordinates of the square's top-left corner
    int startX = centerX - (squareSize / 2);
    int startY = centerY - (squareSize / 2);

    // Draw the square
    SDL_Rect squareRect = { startX, startY, squareSize, squareSize };
    SDL_RenderFillRect(renderer, &squareRect);
}


void drawStones(SDL_Renderer* renderer, int move_count, Board* board) //const GameData& gameData, int move_count) 
{
    //const auto& move = gameData.moves;

    int cellSize = (WINDOW_WIDTH - 2 * BOARD_MARGIN) / (sqrt(board->size()) - 1);
    int radius = cellSize / 2;

    for (int i = 0; i < board->size(); i++)
    {
        Node* node = board->get_node(i);

        if (node->get_player() == '.') continue;

        int x = cellSize * (board->get_x(i)) + BOARD_MARGIN;
        int y = cellSize * (board->get_y(i)) + BOARD_MARGIN;

        //std::cout<<"test:"<<"x: "<<x<<" y: "<<y<<std::endl;
        if (board->get_node(i)->get_player() == 'B') 
        { 
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        } 
        else 
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        drawSquare(renderer, x, y, radius);
    }
}

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


    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow
    (
        "Go Board",
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (!window) 
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer
    (
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    
    if (!renderer) 
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Event e;
    while(is_running)
    {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) 
            {
                is_running = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) 
            {
                /*
                if(move_count == gameData.moves.size())
                {
                    handleMouseClick(e, gameData);
                    //print_array(board, gameData.boardSize);
                    move_count++;
                }
                */
                
            } 
            else if (e.type == SDL_KEYDOWN) 
            {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        cycle--;
                        std::cout << "cycle: " << cycle << std::endl;
                        break;
                    case SDLK_RIGHT:
                        cycle++;
                        std::cout << "cycle: " << cycle << std::endl;
                        break;
                    case SDLK_BACKSPACE:
                        break;
                    case SDLK_s:
                        break;
                    case SDLK_q:
                        is_running = false;
                        break;
                }
                std::cout<< "move: "<< cycle  <<std::endl;

            }
        }
        int x = moves[cycle].first;
        int y = moves[cycle].second;
    
        if (board.add_move(moves[cycle].first, moves[cycle].second, player)) // setting x and y to board and checking legality
            std::cerr << "Error: bad move" << std::endl;

        board.update();             

        if(player == 'W') player = 'B';     
        else player = 'W';        
        
        if (cycle == moves.size() - 1) is_running = false;


        std::cout << "groups: " << std::endl;   
        board.print_group();

        SDL_SetRenderDrawColor(renderer, 255, 204, 153, 255); 
        SDL_RenderClear(renderer);

        drawBoard(renderer, board.size());
        drawStones(renderer, cycle, &board);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    std::cout << "terminated." << std::endl;

    return 0;
}