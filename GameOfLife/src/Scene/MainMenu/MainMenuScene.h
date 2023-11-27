#pragma once

#include <SDL.h>
#include <memory>
#include <vector>

#include "../Scene.h"
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
	SceneManager* m_SceneManager;

	SDL_Color m_MainButtonColor = { 225, 146, 10, 255 };
	SDL_Color m_MainButtonColorHover = { 225, 174, 0, 255 };

	std::vector<Button> m_Buttons;
};