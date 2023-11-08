#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL.h>

#include "SceneManager/SceneManager.h"
#include "GameBoard/GameBoard.h"
#include "Scene/GameScene/GameScene.h"
#include "Scene/EditorScene/EditorScene.h"
#include "Scene/MainMenu/MainMenuScene.h"
#include "Scene/Scene.h"
#include "FileManager/FileManager.h"

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

	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);
	std::cout << "Width: " << mode.w << "\nHeight: " << mode.h;

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

	fileManager::FileManager fm("settings/save.txt");

	fm.saveToFile();

	SDL_Event event;
	/*
	SceneManager sceneManager;

	sceneManager.registerScene<GameScene>("Game Scene");
	*/

	while (!exit)
	{
		frameStart = SDL_GetTicks();
		

		if (SDL_PollEvent(&event) != 0 && event.type == SDL_QUIT)
			exit = true;

		//sceneManager.getCurrentScene()->update(renderer);

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