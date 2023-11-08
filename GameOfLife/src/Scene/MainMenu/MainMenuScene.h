#pragma once

#include <SDL.h>

class MainMenuScene : Scene
{
public:
	MainMenuScene();

	void update(SDL_Renderer* renderer) override;
};