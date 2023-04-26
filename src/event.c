#include "event.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>


Action handleEvents() {
    static SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            return Quit;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                case SDLK_q:
                    return Quit;
                    break;
                case SDLK_SPACE:
                    return Solve;
                    break;
            }
        }
    }

    return None;
}
