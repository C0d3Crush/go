#include "Board.h"

#include <SDL2/SDL.h>
#include <cmath>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int BOARD_MARGIN = 30;

int main (int argc, char** argv)
{
    int cycle = 0;
    int move_count = 0;
    char player = 'B';
    bool is_running = true;

    std::vector<Node> nodes;
    std::vector<Board> boards;
    
    if (argc == 1 )
    {
        std::cout << "empty board:" << std::endl;
        boards.push_back(Board(9, nodes));
    }
    /*else if (argc == 2)
    {
        std::cout << "filled board:" << std::endl;
        boards.push_back(Board(9, nodes, argv[1]));
    }*/
   else 
   {

   }

    Board* board = &boards[0];


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
                is_running = false;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) 
            {
                if(board->get_up_to_date())
                {
                    board->handle_mouse_click(e, &player, &cycle);
                    //board->update(player);     
                }
                
            } 
            else if (e.type == SDL_KEYDOWN) 
            {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        if (cycle > 0) cycle--;
                        break;
                    case SDLK_RIGHT:
                        if (cycle < board->get_moves_size()) cycle++;
                        break;
                    case SDLK_BACKSPACE:
                        break;
                    case SDLK_r:
                        //board->reset();
                        //cycle = 0;
                        break;
                    case SDLK_q:
                        is_running = false;
                        break;
                }
            }
        }

        board->update();
        
        SDL_SetRenderDrawColor(renderer, 255, 204, 153, 255); 
        SDL_RenderClear(renderer);

        board->draw(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    std::cout << "terminated." << std::endl;

    return 0;
}