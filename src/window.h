#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#define WINDOW_WIDTH  1000 // 1400
#define WINDOW_HEIGHT 1000 // 800

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Window;

#include "maze.h"

int init(Window* window);
void render(Window* window, Maze* maze);
void renderTile(Window* window, Maze* maze, int index);
void quit(Window* window);

#endif // WINDOW_H
