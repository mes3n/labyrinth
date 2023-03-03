#ifndef MAZE_H
#define MAZE_H

#define MAZE_WIDTH  200
#define MAZE_HEIGHT 200
#define MAZE_SIZE (MAZE_WIDTH * MAZE_HEIGHT)

#define NONE 0
#define PATH 1
#define WALL 2

typedef struct {
    char tiles[MAZE_SIZE];
} Maze;

#include "window.h"

void genMaze(Maze* maze, Window* window);

#endif // MAZE_H
