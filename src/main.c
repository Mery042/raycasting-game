#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <math.h>

#include "boundary.h"
#include "ray.h"
#include "player.h"

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char *argv[]) {
	SDL_bool running;
	SDL_Window *window2D, *window3D;
	int window_width = 640, window_height = 480;
    SDL_Renderer *renderer2D, *renderer3D;

	SDL_Event event;					// Declare event handle
	float deltaX;

	Player* player = player_create(vector_create(window_width/2, window_height/2));

	float scene[NRAYS];

	time_t t;
	srand((unsigned) time(&t));
	size_t NWALLS = 10;
	Boundary* walls[NWALLS];

	walls[0] = boundary_create(vector_create(0,0), vector_create(window_width,0));
	walls[1] = boundary_create(vector_create(window_width,0), vector_create(window_width,window_height));
	walls[2] = boundary_create(vector_create(window_width,window_height), vector_create(0,window_height));
	walls[3] = boundary_create(vector_create(0,window_height), vector_create(0,0));

	for(int i = 4; i < NWALLS; i++){
		float x1 = rand() % window_width;
		float x2 = rand() % window_width;
		float y1 = rand() % window_height;
		float y2 = rand() % window_height;
		walls[i] = boundary_create(vector_create(x1,y1), vector_create(x2,y2));
	}

	SDL_Init(SDL_INIT_VIDEO);	// SDL2 initialization
	SDL_Init(SDL_INIT_EVENTS);

	// 2D VIEW
	window2D = SDL_CreateWindow(	// Create a window
		"Raycaster",
		10,
		100,
		window_width,
		window_height,
		SDL_WINDOW_SHOWN
	);

	// Check that the window was successfully made
	if (window2D == NULL) {
		// In the event that the window could not be made...
		SDL_Log("Could not create window: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

    renderer2D = SDL_CreateRenderer(window2D, -1, SDL_RENDERER_ACCELERATED);
    if (renderer2D == NULL) {
		// In the event that the window could not be made...
		SDL_Log("Could not create renderer: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// 3D VIEW
	window3D = SDL_CreateWindow(	// Create a window
		"Raycaster",
		700,
		100,
		window_width,
		window_height,
		SDL_WINDOW_SHOWN
	);

	// Check that the window was successfully made
	if (window3D == NULL) {
		// In the event that the window could not be made...
		SDL_Log("Could not create window: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

    renderer3D = SDL_CreateRenderer(window3D, -1, SDL_RENDERER_ACCELERATED);
    if (renderer3D == NULL) {
		// In the event that the window could not be made...
		SDL_Log("Could not create renderer: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	//SDL_ShowCursor(SDL_DISABLE);
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_WarpMouseInWindow(window3D, window_width / 2, window_height / 2);

	running = SDL_TRUE;

	// user-defined code here...

	while (running) {
		while (running && SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_WINDOWEVENT:
					if(event.window.event == SDL_WINDOWEVENT_CLOSE){
						running = SDL_FALSE;
					}
					break;

				case SDL_MOUSEMOTION:
					deltaX = (float)event.motion.x - window_width/2;
				
					player_rotate(player, DEG2RAD(deltaX));
					SDL_WarpMouseInWindow(window3D, window_width / 2, window_height / 2);
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						//case SDLK_q:  player_move(player, -0.1); break;
						//case SDLK_d: player_move(player, 0.1); break;
						case SDLK_z: player_move(player, 1.5); break;
						case SDLK_s: player_move(player, -1.5); break;
						case SDLK_KP_MINUS: player_updateFOV(player, -5); break;
						case SDLK_KP_PLUS: player_updateFOV(player, 5); break;
					}
					break;

			}
		}

        SDL_SetRenderDrawColor(renderer2D, 10, 10, 10, 255);
		SDL_SetRenderDrawColor(renderer3D, 10, 10, 10, 255);
		SDL_RenderClear(renderer2D);
		SDL_RenderClear(renderer3D);

		/*---------------------------------------------------------------------*/
		for(int i = 0; i < sizeof(walls)/sizeof(walls[0]); i++){
			boundary_draw(walls[i], renderer2D, 0, 225, 0, SDL_ALPHA_OPAQUE);
		}
        
		double distProjPlane = window_width / 2.0 / tan(player_getFOV(player) / 2.0); // projection plane is required for fisheye fix
		player_look(scene, player, walls, NWALLS, renderer2D, 225, 225, 225);

		const int w = window_width / (sizeof(scene)/sizeof(scene[0]));
		for(int i = 0; i < player_getFOV(player) - 1; i++){
			const float iSq = scene[i]*scene[i];
			const int wSq = window_width*window_width;
			const int b = map(iSq, 0, wSq, 255, 0);
			//const int h = map(scene[i], 0, window_width, window_height, 0);
			const double h = (window_width / scene[i]) * distProjPlane; // fisheye fix
			SDL_SetRenderDrawColor(renderer3D, 0, b, 0, 255);
			SDL_Rect rectA = {i * w + w / 2, window_height/2 - h / 2, w, h};
			SDL_RenderFillRect(renderer3D, &rectA);
		}
		/*---------------------------------------------------------------------*/

        SDL_RenderPresent(renderer2D);
		SDL_RenderPresent(renderer3D);
	}
	
    SDL_DestroyRenderer(renderer2D);
	SDL_DestroyRenderer(renderer3D);
	SDL_DestroyWindow(window2D);		// Close and destroy the window
	SDL_DestroyWindow(window3D);
	SDL_Quit();						// Clean up
	return 0;
}