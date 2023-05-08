#include "maze.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <stdio.h>

int getNeighbors(int index, int* neighbors) {

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

int getCorners(int index, int prev, int* neighbors) {

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

void initMaze(Maze* maze) {
    memset(maze->tiles, Clear, sizeof(maze->tiles));
    srand(time(NULL));

    int start = rand() % MAZE_SIZE;
    maze->start = start;
    maze->end = start;
    maze->state = Generating;
}

void genMaze(Maze* maze) {
    initMaze(maze);

    int path[MAZE_SIZE] = { 0 };
    int pathTop = 0;

    int index = maze->start;
    maze->tiles[index] = Path;
    do {

        int neighbors[4] = { 0 };
        int count = getNeighbors(index, neighbors);

        // for (int i = 0; i < pathTop; i++) {
        //     printf("%d, ", path[i]);
        // }
        // printf("\n");
        
        for (int i = 0; i < count; i++) {
            if (maze->tiles[neighbors[i]] == Clear) {  // possible tile
                int nn[6];
                int cc = getNeighbors(neighbors[i], &nn[0]);
                cc += getCorners(neighbors[i], index, &nn[cc]);
                for (int j = 0; j < cc; j++) {
                    if (maze->tiles[nn[j]] == Path && nn[j] != index) {  // paths should never intercept
                        maze->tiles[neighbors[i]] = Wall;  // contains paths on two sides, not accessible
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

    } while (pathTop > 0);

    maze->state = Done;
}

int stepMaze(Maze* maze, int* path, int* pathTop) {
    int index = path[*pathTop - 1];
    int neighbors[4] = { 0 }; 
    int count = getNeighbors(index, neighbors);

    for (int i = 0; i < count; i++) {
        if (maze->tiles[neighbors[i]] == Clear) {  // possible tile
            int nn[6];
            int cc = getNeighbors(neighbors[i], &nn[0]);
            cc += getCorners(neighbors[i], index, &nn[cc]);
            for (int j = 0; j < cc; j++) {
                if (maze->tiles[nn[j]] == Path && nn[j] != index) {  // paths should never intercept
                    maze->tiles[neighbors[i]] = Wall;  // contains paths on two sides, not accessible
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

    maze->tiles[index] = Path;
    if (count == 0) {  // no tile was found -> go back
        *pathTop -= 1; 
    }
    else {
        path[(*pathTop)++] = neighbors[rand() % count];
        return 1;
    }
    
    if (*pathTop < 0) {
        maze->state = Done;
    }
    return 0;
}

