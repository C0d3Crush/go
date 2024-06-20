#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

#include <SDL2/SDL.h>
#include "../logic/Board.h"

class SDLRenderer
{
public:
    SDLRenderer() : window(nullptr), renderer(nullptr) {}
    ~SDLRenderer() {}

    bool init(int width, int height);
    bool handleEvents(Board* board, char* player);
    void render(Board* board);
    void cleanup();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // SDL_RENDERER_H
