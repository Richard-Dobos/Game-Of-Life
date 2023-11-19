#pragma once

#include "../../GameBoard/GameBoard.h"
#include "../Scene.h"
#include "../../Camera/Camera.h"

class EditorScene : public Scene
{
public:
	EditorScene(SDL_Event* e)
		:Scene(e) {}

	void update(SDL_Renderer* renderer) override;
	void loadSettings() override
	{};

	void renderBoardSettingsMenu(SDL_Renderer* renderer);

private:
	void checkForSettingsShortcut();

private:
	bool m_RenderBoardSettings = true;

	WindowProperties m_WindowProperties;
	GameBoard m_GameBoard;
	Camera m_Camera;
};