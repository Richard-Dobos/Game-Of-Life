#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL.h>

#include "GameBoard/GameBoard.h"

int main()
{
	const int WIDTH = 1280;
	const int HEIGHT = 720;

	SDL_Window* window = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cout << "Couldn't init SDL.\n";
		return 0;
	}

	if (!window)
	{
		std::cout << "Couldn't init window!\n";
		SDL_Quit();
		return 0;
	}

	if (!renderer)
	{
		std::cout << "Couldn't init render\n";
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 0;
	}

	bool exit = false;

	const int FPS = 1;
	uint32_t frameStart;
	int frameTime;
	
	std::vector<std::vector<bool>> data = 
	{ 
		{false, false, false, false, false, false, false},
		{true, true, true, false, true, true, false}, 
		{false, true, true, false, true, true, false},
		{false, false, false, false, false, false, false}
	};
	
	/*
	std::vector<std::vector<bool>> data = {
		{ false, false, false, false, false, false, false },
		{ false, true, false, false, true, false, false },
		{ false, false, true, false, false, true, false },
		{ false, false, false, false, false, false, false }
	};
	*/

	GameBoard gameBoard(1280, 720, 10, data);
	
	gameBoard.printAliveCellsData();
	std::cout << '\n';

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawPoint(renderer, 20, 20);

	while (!exit)
	{
		frameStart = SDL_GetTicks();
		
		gameBoard.update();
		std::cout << '\n';

		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - frameStart;

		if (1000 / FPS > frameTime)
		{
			SDL_Delay(1000 / FPS - frameTime);
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 1;
}