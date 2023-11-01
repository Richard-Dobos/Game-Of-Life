#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL.h>

#include "GameBoard/GameBoard.h"
#include "Scene/GameScene/GameScene.h"

int main()
{
	const int WIDTH = 1280;
	const int HEIGHT = 720;

	SDL_Window* window = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

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

	const int FPS = 20;
	uint32_t frameStart;
	uint32_t frameTime; 
	
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


/*
	Game Game(1280, 720, data);
	
	loop:
		if sceneManager.scene == editor
			sceneManager.scene.update() =>
			{
				setData()
			}

		else 
			sceneManager.scene.update()

	*/
	
	GameScene gameScene(1280, 720, data[0].size(), data.size());
	SDL_Event event;

	SDL_BUTTON(1);

	while (!exit)
	{
		frameStart = SDL_GetTicks();
		
		if (SDL_PollEvent(&event) != 0 && event.type == SDL_QUIT)
			exit = true;

		gameScene.update(renderer);

		frameTime = SDL_GetTicks() - frameStart;

		if (1000 / FPS > frameTime)
		{
			SDL_Delay(1000 / FPS - frameTime);
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 1;
}