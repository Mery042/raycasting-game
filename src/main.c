#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "boundary.h"

int main(int argc, char *argv[]) {
	SDL_bool running;
	SDL_Window *window;
    SDL_Renderer* renderer;
	SDL_Event event;					// Declare event handle

	SDL_Init(SDL_INIT_VIDEO);			// SDL2 initialization

	window = SDL_CreateWindow(	// Create a window
		"Raycaster",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_SHOWN
	);

	// Check that the window was successfully made
	if (window == NULL) {
		// In the event that the window could not be made...
		SDL_Log("Could not create window: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
		// In the event that the window could not be made...
		SDL_Log("Could not create renderer: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

    Point* a = point_create(1,1);
    Point* b = point_create(100,100);
    Boundary* boundary = boundary_create(*a, *b);

	running = SDL_TRUE;

	// user-defined code here...

	while (running) {
		while (running && SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {			// In case of exit
					running = SDL_FALSE;
					break;
				}
			}
		}

        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
		SDL_RenderClear(renderer);
        boundary_draw(boundary, renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderPresent(renderer);
	}
	
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);		// Close and destroy the window
	SDL_Quit();						// Clean up
	return 0;
}