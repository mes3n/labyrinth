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
    // genMaze(&maze);
    initMaze(&maze);
    int *path = malloc(sizeof(int) * MAZE_SIZE);
    int pathTop = 0;
    path[pathTop++] = maze.start;

    int mainloop = 1;
    while (mainloop) {
        switch (handleEvents()) {
        case Quit:
            mainloop = 0;
            break;
        case Solve:
            maze.state = maze.state == Generating ? Generating : Solving;
            break;
        case None:
        default:
            break;
        }
        
        if (maze.state == Generating) {
            if (stepMaze(&maze, path, &pathTop)) {
                // renderTile(&window, &maze, path[pathTop - 1]);
                render(&window, &maze);
            }
            else if (pathTop < 0) {
                free(path);
            }
        }
        else if (maze.state == Solving) {
            
        }
        else {
            render(&window, &maze);
        }
    }

    quit(&window);
    return 0;
}

