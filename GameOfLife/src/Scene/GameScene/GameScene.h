#pragma once

#include <vector>

#include "SDL.h"
#include "../Scene.h"
#include "../../GameBoard/GameBoard.h"
#include "../../Camera/Camera.h"

class GameScene : public Scene
{
public:
	GameScene(SDL_Event* e)
		:Scene(e) {}

	void initScene(int screenWidth, int screenHeight, int gameBoardWidth, int gameBoardHeight);

	void update(SDL_Renderer* renderer) override;

private:
	GameBoard m_GameBoard;
	Camera m_Camera;

	int m_ScreenWidth, m_ScreenHeight, m_GameBoardWidth, m_GameBoardHeight, m_MouseX, m_MouseY;
};