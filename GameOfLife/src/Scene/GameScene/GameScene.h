#pragma once

#include <vector>

#include "SDL.h"
#include "../Scene.h"
#include "../../GameBoard/GameBoard.h"
#include "../../Camera/Camera.h"
#include "../../WindowProperties.h"

class GameScene : public Scene
{
public:
	GameScene(SDL_Event* e)
		:Scene(e) {}

	void update(SDL_Renderer* renderer) override;
	void loadSettings() override
	{};

private:
	WindowProperties m_WindowProperties;
	GameBoard m_GameBoard;
	Camera m_Camera;

	int m_ScreenWidth, m_ScreenHeight, m_GameBoardWidth, m_GameBoardHeight, m_MouseX, m_MouseY;
};