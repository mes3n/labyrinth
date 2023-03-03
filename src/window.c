#include "window.h"

#include <stdio.h>

#define BACKGROUND_COLOR 0x18, 0x18, 0x18, 0xff

int init(Window* window) {
    window->window = NULL;
    window->renderer = NULL;
    //  window->surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return -1;
    }

    window->window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
        WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window->window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return -1;
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (window->renderer == NULL) {
        fprintf(stderr, "could not create renderer: %s\n", SDL_GetError());
        return -1;
    }

    //  window->surface = SDL_GetWindowSurface(window->window);
    //  if (window->surface == NULL) {
    //    fprintf(stderr, "could not create surface: %s\n", SDL_GetError());
    //    return -1;
    //  }

    return 0;
}

void render(Window* window, Maze* maze) {
    SDL_SetRenderDrawColor(window->renderer, BACKGROUND_COLOR); // gray background
    SDL_RenderClear(window->renderer);

    const int tileW = WINDOW_WIDTH / MAZE_WIDTH;
    const int tileH = WINDOW_HEIGHT / MAZE_HEIGHT;

    for (int i = 0; i < MAZE_SIZE; i++) {
        if (maze->tiles[i] == PATH) {
            SDL_SetRenderDrawColor(window->renderer, 0xcd, 0xcd, 0xcd, 0xff); // gray background
            SDL_Rect rect = { (i % MAZE_WIDTH) * tileW, (i / MAZE_WIDTH) * tileH, tileW, tileH };
        
            SDL_RenderFillRect(window->renderer, &rect);
        }
    }

    SDL_RenderPresent(window->renderer);
}

void quit(Window* window) {
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    SDL_Quit();
}
