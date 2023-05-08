#include "window.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#define BACKGROUND_COLOR 0x18, 0x18, 0x18, 0xff

int init(Window* window) {
    window->window = NULL;
    window->renderer = NULL;
    //  window->surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return -1;
    }

    window->window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
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
    
    SDL_Rect rect; 
    for (int i = 0; i < MAZE_SIZE; i++) {
        rect.x = (i % MAZE_WIDTH) * tileW;
        rect.y = (i / MAZE_WIDTH) * tileH;
        rect.w = tileW;
        rect.h = tileH;
        switch (maze->tiles[i]) {
        case Path:
            SDL_SetRenderDrawColor(window->renderer, i == maze->end ? 0x00 : 0xcd, i == maze->start ? 0x00 : 0xcd, 0xcd, 0xff); // white path
            SDL_RenderFillRect(window->renderer, &rect);
            break;
        case Wall:
            // SDL_SetRenderDrawColor(window->renderer, 0x00, 0x22, 0xaa, 0xff); // white path
            // SDL_RenderFillRect(window->renderer, &rect);
            break;
        default:
            break;
        }

    }

    SDL_RenderPresent(window->renderer);
}

void renderTile(Window *window, Maze *maze, int index) {
    const int tileW = WINDOW_WIDTH / MAZE_WIDTH;
    const int tileH = WINDOW_HEIGHT / MAZE_HEIGHT;

    SDL_Rect rect; 
    rect.x = (index % MAZE_WIDTH) * tileW;
    rect.y = (index / MAZE_WIDTH) * tileH;
    rect.w = tileW;
    rect.h = tileH;

    // SDL_RenderSetClipRect(window->renderer, &rect);

    // SDL_SetRenderDrawColor(window->renderer, BACKGROUND_COLOR); // gray background
    // SDL_RenderClear(window->renderer);

    SDL_SetRenderDrawColor(window->renderer, 0xcd, 0xcd, 0xcd, 0xff); // white path
    SDL_RenderFillRect(window->renderer, &rect);

    SDL_RenderPresent(window->renderer);
}

void quit(Window* window) {
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    SDL_Quit();
}

