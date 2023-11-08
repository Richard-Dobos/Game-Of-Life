#pragma once

#include <vector>

#include "SDL.h"
#include "../Scene.h"
#include "../../GameBoard/GameBoard.h"
#include "../../Camera/Camera.h"


class GameScene : Scene
{
public:
	GameScene();

	void initScene(int screenWidth, int screenHeight, int gameBoardWidth, int gameBoardHeight);

	void update(SDL_Renderer* renderer) override;

private:
	GameBoard m_GameBoard;
	Camera m_Camera;

	int m_ScreenWidth, m_ScreenHeight, m_GameBoardWidth, m_GameBoardHeight;
};	