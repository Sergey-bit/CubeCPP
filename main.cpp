#include <iostream>
#include <SDL.h>
#include "Cube.hpp"

const int width = 800;
const int height = 760;

void main_loop(SDL_Renderer*);

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	if (SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &window, &renderer))
	{
		std::cerr << "Failed to create window and renderer: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_SetWindowTitle(window, "Cube");

	main_loop(renderer);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}

void main_loop(SDL_Renderer* renderer)
{
	SDL_Event event;
	Cube cube(renderer, width / 2, height / 2, 0.0, 100);

	while (true)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
		{
			break;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Draw
		SDL_SetRenderDrawColor(renderer, 53, 219, 58, 255);
		cube.draw();

		// Rotation
		cube.rotateX(cube.degreeToRadians(0.005));
		cube.rotateY(cube.degreeToRadians(0.005));
		cube.rotateZ(cube.degreeToRadians(0.005));

		SDL_RenderPresent(renderer);
	}
}