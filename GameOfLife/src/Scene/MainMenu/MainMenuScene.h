#pragma once

#include <SDL.h>
#include <memory>
#include <vector>

#include "../Scene.h"
#include "../../Text/Text.h"
#include "../../Input/Button/Button.h"
#include "../../Scene/GameScene/GameScene.h"
#include "../../SceneManager/SceneManager.h"
#include "../../Scene/EditorScene/EditorScene.h"

class MainMenuScene : public Scene
{
public:
	MainMenuScene(SDL_Event* e, WindowProperties* windowProperites, SceneManager* sceneManager);

	void update(SDL_Renderer* renderer) override;
	
private:
	std::vector<Button> m_Buttons;

	SDL_Color m_ButtonColor = { 225, 146, 10, 255 };
	SDL_Color m_ButtonColorHover = { 225, 174, 0, 255 };
	SDL_Color m_ButtonTextColor = { 40, 40, 40, 255 };

	SceneManager* m_SceneManager;
};