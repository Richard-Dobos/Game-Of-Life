#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL.h>

#include "SceneManager/SceneManager.h"
#include "FileManager/FileManager.h"
#include "Scene/MainMenu/MainMenuScene.h"
#include "Scene/GameScene/GameScene.h"
#include "Scene/EditorScene/EditorScene.h"

int main()
{
	const int WIDTH = 1280;
	const int HEIGHT = 720;

	SDL_Window* window = SDL_CreateWindow("Game Of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetWindowResizable(window, SDL_FALSE);
	SDL_SetWindowBordered(window, SDL_TRUE);
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

	const int FPS = 60;
	uint32_t frameStart;
	uint32_t frameTime;

	std::vector<std::vector<bool>> data =
	{
		{false, false, false, false, false, false, false},
		{true, true, true, false, true, true, false},
		{false, true, true, false, true, true, false},
		{false, false, false, false, false, false, false}
	};

	SDL_Event event;
	FileManager fm("settings/save.txt");

	SceneManager sceneManager(&fm);

	sceneManager.registerScene<MainMenuScene>("Main Menu", &event);
	sceneManager.registerScene<EditorScene>("Editor", &event);
	
	sceneManager.changeScene("Editor");

	while (!exit)
	{
		frameStart = SDL_GetTicks();

		SDL_PollEvent(&event);

		SDL_SetRenderDrawColor(renderer, 40, 40, 20, 255);
		SDL_RenderClear(renderer);

		sceneManager.getCurrentScene()->update(renderer);

		SDL_RenderPresent(renderer);

		if (event.type == SDL_QUIT)
			exit = true;

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