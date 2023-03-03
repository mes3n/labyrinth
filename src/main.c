// #include <SDL2/SDL.h>
// #include <stdio.h>

#include "event.h"
#include "window.h"
#include "maze.h" 


int main(void) {

    Window window;
    if (init(&window) < 0) {
        return 1;
    }

    Maze maze;
    genMaze(&maze, &window);    

    int mainloop = 1;
    while (mainloop) {
        switch (handleEvents()) {
        case Quit:
            mainloop = 0;
            break;
        case None:
        default:
            break;
        }

        render(&window, &maze);
    }

    quit(&window);
    return 0;
}
