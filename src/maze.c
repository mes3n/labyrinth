#include "maze.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <stdio.h>

static int getNeighbors(int index, int* neighbors) {

    int count = 0;

    if (index % MAZE_WIDTH > 0) {  // not on left edge
        neighbors[count++] = index - 1;
    }
    if (index % MAZE_WIDTH < MAZE_WIDTH - 1) {  // not on right edge
        neighbors[count++] = index + 1;
    }
    if (index / MAZE_WIDTH > 0) {  // not on top edge
        neighbors[count++] = index - MAZE_WIDTH;
    }
    if (index / MAZE_WIDTH < MAZE_HEIGHT - 1) {  // not on bottom edge
        neighbors[count++] = index + MAZE_WIDTH;
    }

    return count;
}

static int getCorners(int index, int prev, int* neighbors) {

    int count = 0;

    if (index - prev == 1) {  // step to the right
        if (index % MAZE_WIDTH == MAZE_WIDTH - 1) return 0;  // right edge
        if (index / MAZE_WIDTH > 0) {  // not on top edge
            neighbors[count++] = index - MAZE_WIDTH + 1;
        }
        if (index / MAZE_WIDTH < MAZE_HEIGHT - 1) {  // not on bottom edge
            neighbors[count++] = index + MAZE_WIDTH + 1;
        }
    }
    else if (index - prev == -1) {  // step to the left
        if (index % MAZE_WIDTH == 0) return 0;  // left edge
        if (index / MAZE_WIDTH > 0) {  // not on top edge
            neighbors[count++] = index - MAZE_WIDTH - 1;
        }
        if (index / MAZE_WIDTH < MAZE_HEIGHT - 1) {  // not on bottom edge
            neighbors[count++] = index + MAZE_WIDTH - 1;
        }
    }
    else if (index - prev == MAZE_WIDTH) {  // step downwards
        if (index / MAZE_WIDTH == MAZE_HEIGHT - 1) return 0;  // bottom edge
        if (index % MAZE_WIDTH > 0) {  // not on left edge
            neighbors[count++] = index + MAZE_WIDTH - 1;
        }
        if (index % MAZE_WIDTH < MAZE_WIDTH - 1) {  // not on right edge
            neighbors[count++] = index + MAZE_WIDTH + 1;
        }
    }
    else if (index - prev == -MAZE_WIDTH) {  // step upwards
        if (index / MAZE_WIDTH == 0) return 0;  // top edge
        if (index % MAZE_WIDTH > 0) {  // not on left edge
            neighbors[count++] = index - MAZE_WIDTH - 1;
        }
        if (index % MAZE_WIDTH < MAZE_WIDTH - 1) {  // not on right edge
            neighbors[count++] = index - MAZE_WIDTH + 1;
        }
    }

    return count;
}


void genMaze(Maze* maze, Window* window) {
    memset(maze->tiles, NONE, MAZE_SIZE);
    srand(time(NULL));

    int start = rand() % MAZE_SIZE;
    int path[MAZE_SIZE] = { 0 };
    int pathTop = 0;

    int index = start;
    do {

        int neighbors[4] = { 0 };
        int count = getNeighbors(index, neighbors);

        // for (int i = 0; i < pathTop; i++) {
        //     printf("%d, ", path[i]);
        // }
        // printf("\n");
        
        for (int i = 0; i < count; i++) {
            if (maze->tiles[neighbors[i]] == NONE) {  // possible tile
                int nn[4];
                int cc = getNeighbors(neighbors[i], nn);
                for (int j = 0; j < cc; j++) {
                    if (maze->tiles[nn[j]] == PATH && nn[j] != index) {  // paths should never intercept
                        maze->tiles[neighbors[i]] = WALL;  // contains paths on two sides, not accessible
                        for (int k = i; k < count - 1; k++) {
                            neighbors[k] = neighbors[k + 1];
                        }
                        count--;
                        i--;
                        break;
                    }
                }
                cc = getCorners(neighbors[i], index, nn);
                for (int j = 0; j < cc; j++) {
                    if (maze->tiles[nn[j]] == PATH) {  // paths should never intercept at corners either
                        maze->tiles[neighbors[i]] = WALL;  // contains paths on two sides, not accessible
                        for (int k = i; k < count - 1; k++) {
                            neighbors[k] = neighbors[k + 1];
                        }
                        count--;
                        i--;
                        break;
                    }
                }
            }
            else {  // tile is either wall or already explored -> remove as neighbor
                for (int j = i; j < count - 1; j++) {
                    neighbors[j] = neighbors[j + 1];
                }
                count--;
                i--;
            }
        }

        maze->tiles[index] = PATH;
        if (count == 0) {  // no tile was found -> go back
            index = path[--pathTop];
        }
        else {
            path[pathTop++] = index;
            index = neighbors[rand() % count];
        }
        
        // for (int i = 0; i < MAZE_SIZE; i++) {
        //     printf("%d ", maze->tiles[i]);
        //     if (i % MAZE_WIDTH == MAZE_WIDTH - 1) printf("\n");
        // }
        // printf("\n");

        // const int tileW = WINDOW_WIDTH / MAZE_WIDTH;
        // const int tileH = WINDOW_HEIGHT / MAZE_HEIGHT;

        // SDL_SetRenderDrawColor(window->renderer, 0xcd, 0xcd, 0xcd, 0xff); // gray background
        // SDL_Rect rect = { (index % MAZE_WIDTH) * tileW, (index / MAZE_WIDTH) * tileH, tileW, tileH };

        // SDL_RenderFillRect(window->renderer, &rect);
        // SDL_RenderPresent(window->renderer);

    } while (pathTop > 0);
}
