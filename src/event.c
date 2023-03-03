#include "event.h"

#include <SDL2/SDL_events.h>

static SDL_Event event;

Action handleEvents() {
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
            }
        }
    }

    return None;
}
