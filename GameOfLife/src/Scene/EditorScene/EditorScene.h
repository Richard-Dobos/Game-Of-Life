#pragma once

#include <vector>
#include <format>

#include "../../Input/Button/Button.h"
#include "../../GameBoard/GameBoard.h"
#include "../Scene.h"
#include "../../Camera/Camera.h"

class EditorScene : public Scene
{
public:
	EditorScene(SDL_Event* e, WindowProperties* windowProperties);

	void update(SDL_Renderer* renderer) override;

	void renderBoardSettingsMenu(SDL_Renderer* renderer) const;

private:
	void checkForSettingsShortcut();
	void addLiveCell();

	bool m_RenderBoardSettings = true;

	int m_BoardSettingsPosX = (m_WindowProperties->windowWidth - m_WindowProperties->windowWidth * 0.15f);

	SDL_Color m_ButtonColor = { 225, 146, 10, 255 };
	SDL_Color m_ButtonHoverColor = { 225, 174, 0, 255 };
	GameBoard m_GameBoard; 
	Camera m_Camera;

	std::vector<Button> m_Buttons;
};