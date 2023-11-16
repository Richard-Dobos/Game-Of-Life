#pragma once

#include <SDL.h>
#include <memory>
#include <map>

#include "../Scene.h"
#include "../../Input/Button/Button.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene(SDL_Event* e);

	void update(SDL_Renderer* renderer) override;

private:
	SDL_Color m_MainButtonColor = { 100, 100, 100, 255 };

	std::vector<Button> m_Buttons;
};