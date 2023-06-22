#ifndef MAZE_H
#define MAZE_H

#define MAZE_WIDTH  100
#define MAZE_HEIGHT 100
#define MAZE_SIZE (MAZE_WIDTH * MAZE_HEIGHT)

// #define NONE 0
// #define PATH 1
// #define WALL 2

typedef enum {
    Clear,
    Path,
    Wall,
    Expl,
    True,
} Tile;

typedef enum {
    Generating,
    Solving,
    Done,
} MazeState;

typedef struct {
    Tile tiles[MAZE_SIZE];
    MazeState state;

    int start;
    int end;
} Maze;

void initMaze(Maze* maze);
void genMaze(Maze* maze);
int stepMaze(Maze* maze, int* path, int* pathTop);
int solveMaze(Maze* maze, int* path, int* pathTop);

#endif // MAZE_H

