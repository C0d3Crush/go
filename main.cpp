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

void drawStones(SDL_Renderer* renderer, Board* board) //const GameData& gameData, int move_count) 
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

void handleMouseClick(const SDL_Event& e, Board* board, char* player, int* cycle, std::vector<std::pair<int, int>>* moves) 
{
    std::cout << ">>===== Handle Mouse =====<<" << std::endl;
    if (e.button.button == SDL_BUTTON_LEFT) 
    {
        // Capture raw mouse coordinates
        int mouseX = e.button.x;
        int mouseY = e.button.y;

        // Calculate cell size
        int boardWidth = board->width();
        int boardHeight = board->height();
        int cellSize = (WINDOW_WIDTH - BOARD_MARGIN * 2) / boardWidth;

        // Adjust mouse coordinates by subtracting the board's margin
        int adjustedMouseX = mouseX - BOARD_MARGIN;
        int adjustedMouseY = mouseY - BOARD_MARGIN;

        // Ensure adjusted coordinates are within valid range
        if (adjustedMouseX < 0 || adjustedMouseX >= (boardWidth * cellSize) || 
            adjustedMouseY < 0 || adjustedMouseY >= (boardHeight * cellSize)) {
            std::cout << "Mouse coordinates out of board bounds!" << std::endl;
            return;
        }

        // Convert adjusted mouse coordinates to grid coordinates with rounding
        int gridX = adjustedMouseX / cellSize;
        int gridY = adjustedMouseY / cellSize;

        // Ensure grid coordinates are within board dimensions
        if (gridX >= boardWidth) gridX = boardWidth - 1;
        if (gridY >= boardHeight) gridY = boardHeight - 1;

        // Ensure the calculated grid position is within the board limits
        if (gridX >= 0 && gridX < board->size() && gridY >= 0 && gridY < board->size()) 
        {
            int index = board->get_index(gridY, gridX);

            std::cout << "index: " <<index << " player at coords: " << board->get_node(index)->get_player() << std::endl;
            
            std::cout << "(" << gridX << "; " << gridY << ")" << std::endl;

            std::cout << "(" << board->get_x(index) << "; "<< board->get_y(index) << ")"<< std::endl;

            if (board->get_node(index)->get_player() == '.') 
            {
                moves->push_back({gridY, gridX});
                (*cycle)++;
            }
            else std::cout << "Cant place there. Space is ocupied." << std::endl;
        }
        else
        {
            std::cout << "Click out of board boundaries!" << std::endl;
        }
    }
}

int main ()
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

    cycle = moves.size();


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
                if(move_count == moves.size())
                {
                    handleMouseClick(e, &board, &player, &cycle, &moves);
                    board.update();     
                }
                
            } 
            else if (e.type == SDL_KEYDOWN) 
            {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        if (cycle > 0) cycle--;
                        break;
                    case SDLK_RIGHT:
                        if (cycle < moves.size()) cycle++;
                        break;
                    case SDLK_BACKSPACE:
                        break;
                    case SDLK_r:
                        board.reset();
                        cycle = 0;
                        break;
                    case SDLK_q:
                        is_running = false;
                        break;
                }
            }
        }

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

            board.update();     
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
                board.update();     
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 255, 204, 153, 255); 
        SDL_RenderClear(renderer);

        drawBoard(renderer, board.size());
        drawStones(renderer, &board);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    std::cout << "terminated." << std::endl;

    return 0;
}