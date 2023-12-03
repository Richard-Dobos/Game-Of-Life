#pragma once

#include <vector>
#include <format>

#include "../Scene.h"
#include "../../Text/Text.h"
#include "../../Camera/Camera.h"
#include "../MainMenu/MainMenuScene.h"
#include "../../GameBoard/GameBoard.h"
#include "../../Input/Button/Button.h"
#include "../../SceneManager/SceneManager.h"


class EditorScene : public Scene
{
public:
	EditorScene(SDL_Event* e, WindowProperties* windowProperties, SceneManager* sceneManager);

	void update(SDL_Renderer* renderer) override;

private:
	void renderBoardSettingsMenu(SDL_Renderer* renderer) const;
	void checkForSettingsShortcut();
	void addLiveCell();
	void saveCellData();

private:
	bool m_RenderBoardSettings = true;
	int m_BoardSettingsPosX = (m_WindowProperties->windowWidth - m_WindowProperties->windowWidth * 0.15f);

	SDL_Color m_ButtonColor = { 225, 146, 10, 255 };
	SDL_Color m_ButtonColorHover = { 225, 174, 0, 255 };
	SDL_Color m_ButtonTextColor = { 40, 40, 40, 255 };

	SceneManager* m_SceneManager;
	GameBoard m_GameBoard; 
	Camera m_Camera;
	
	std::vector<Button> m_Buttons;
};