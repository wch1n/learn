#include <SDL.h>
#include <stdio.h>

int main(int argv, char *argc[])
{
	int quit = 1;
	SDL_Event event;
	SDL_Window *window = NULL;
	SDL_Renderer *render = NULL;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	window = SDL_CreateWindow("SDL2 Window",
			200,
			200,
			640,
			480,
			SDL_WINDOW_SHOWN);

	if (!window) {
		printf("Failed to Create Window!");
		goto __EXIT;
	}

	render = SDL_CreateRenderer(window, -1, 0);
	if (!render) {
                SDL_Log("Failed to Create Render!");
                goto __DESTROY_WINDOW;
        }

	SDL_RenderClear(render);
	SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	SDL_RenderPresent(render);
	//SDL_Delay(30000);

	SDL_Texture *texture = SDL_CreateTexture(render,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			600,
			450);

	if (!texture) {
		SDL_Log("Failed to Create Texture!");
		goto __RENDER;
	}

	do {
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				quit = 0;
				break;
			default:
				SDL_Log("Event type is %d", event.type);
				break;
		}



	} while (quit);

	SDL_DestroyTexture(texture);

__RENDER:
	SDL_DestroyRenderer(render);

__DESTROY_WINDOW:
	SDL_DestroyWindow(window);

__EXIT:
	SDL_Quit();
	return 0;
}

