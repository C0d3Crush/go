#include "Sdl_renderer.h"

#include <iostream>

bool SDLRenderer::init(int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Go Board", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) 
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) 
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    return true;
}

bool SDLRenderer::handleEvents(Board* board, char* player)
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) 
    {
        if (e.type == SDL_QUIT) 
        {
            return false;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) 
        {
            board->handle_mouse_click(e, player);
            //board->set_cycle(board->get_cycle() + 1);
        }
        else if (e.type == SDL_KEYDOWN) 
        {
            switch (e.key.keysym.sym) 
            {
                case SDLK_LEFT:
                    if (board->get_cycle() > 0) board->set_cycle(board->get_cycle() - 1);
                    break;
                case SDLK_RIGHT:
                    if (board->get_cycle() < board->get_moves_size()) board->set_cycle(board->get_cycle() + 1);
                    break;
                case SDLK_q:
                    return false;
                    break;
                case SDLK_s:
                    std::cout << "saving..." <<std::endl;
                    File_manager file_manager;
                    file_manager.saveSGF("../src/file/data/current.sgf", board->size(), board->get_komi(), board->get_ruleset(), board->get_result(), board->get_black_player(), board->get_white_player(), board->get_moves());
            }
        }
    }
    return true;
}

void SDLRenderer::render(Board* board)
{
    SDL_SetRenderDrawColor(renderer, 255, 204, 153, 255); 
    SDL_RenderClear(renderer);
    board->draw(renderer);
    SDL_RenderPresent(renderer);
}

void SDLRenderer::cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
