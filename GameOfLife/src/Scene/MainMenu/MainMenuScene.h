#pragma once

#include <SDL.h>
#include <memory>
#include <vector>

#include "../Scene.h"
#include "../../Input/Button/Button.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene(SDL_Event* e, WindowProperties* windowProperites);

	void update(SDL_Renderer* renderer) override;
	
private:
	SDL_Color m_MainButtonColor = { 100, 100, 100, 255 };
	SDL_Color m_MainButtonColorHover = { 100, 100, 100, 255 };

	std::vector<Button> m_Buttons;
};