// #include <SDL2/SDL.h>
// #include <stdio.h>

#include "event.h"
#include "window.h"
#include "maze.h" 

#include <stdlib.h>


int main(void) {

    Window window;
    if (init(&window) < 0) {
        return 1;
    }

    Maze maze;
    initMaze(&maze);

    // Generation variables
    int *path = malloc(sizeof(int) * MAZE_SIZE);
    int pathTop = 0;
    int maxLenPath = 0;
    path[pathTop++] = maze.start;

    int mainloop = 1;
    while (mainloop) {
        switch (handleEvents()) {
        case Quit:
            mainloop = 0;
            break;
        case Solve:
            if (maze.state != Generating) {
                path = malloc(sizeof(int) * MAZE_SIZE);
                pathTop = 0;
                path[pathTop++] = maze.start;

                maze.state = Solving;
            }
            break;
        case None:
        default:
            break;
        }
        
        if (maze.state == Generating) {
            if (stepMaze(&maze, path, &pathTop)) {
                // renderTile(&window, &maze, path[pathTop - 1]);
                render(&window, &maze);

                if (pathTop > maxLenPath) {
                    maze.end = path[pathTop - 1];
                    maxLenPath = pathTop;
                }
            }
            else if (pathTop < 0) {
                free(path);
            }
        }
        else if (maze.state == Solving) {
            if (solveMaze(&maze, path, &pathTop)) {
                // renderTile(&window, &maze, path[pathTop - 1]);
                render(&window, &maze);
            }
            else if (maze.state == Done) {
                for (int i = 0; i < pathTop; i++) {
                    maze.tiles[path[i]] = True;
                }
                free(path);
            }
        }
        else {
            render(&window, &maze);
        }
    }

    quit(&window);
    return 0;
}

