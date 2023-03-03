#include <SDL2/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main (void) {
	
	SDL_Window* window = NULL;
	SDL_Surface* surface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}
	window = SDL_CreateWindow(
		"Hello World",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (window == NULL) {
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
		return 1;
	}

	surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

