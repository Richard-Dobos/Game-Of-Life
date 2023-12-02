#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <iostream>

#include "Scene/GameScene/GameScene.h"
#include "SceneManager/SceneManager.h"
#include "Scene/MainMenu/MainMenuScene.h"
#include "Scene/EditorScene/EditorScene.h"

#ifdef _DEBUG
int main()
#else 
int WinMain()
#endif
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

	uint32_t frameStart;
	uint32_t frameTime;

	SDL_Event event;
	WindowProperties windowProperties = { HEIGHT, WIDTH, 30, false };
	SceneManager sceneManager(&event, &windowProperties);

	sceneManager.setStartScene<GameScene>();

	while (!windowProperties.exit)
	{
		frameStart = SDL_GetTicks();

		SDL_PollEvent(&event);

		sceneManager.update(renderer);

		SDL_RenderPresent(renderer);

		if (event.type == SDL_QUIT)
			windowProperties.exit = true;

		frameTime = SDL_GetTicks() - frameStart;

		if (1000 / windowProperties.refreshRate > frameTime)
		{
			SDL_Delay(1000 / windowProperties.refreshRate - frameTime);
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 1;
}
