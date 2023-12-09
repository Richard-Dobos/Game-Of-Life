#pragma once

#include <SDL.h>
#include <vector>
#include <thread>
#include <future>

#include "../Scene.h"
#include "../../Camera/Camera.h"
#include "../../GameBoard/GameBoard.h"
#include "../../WindowProperties.h"
#include "../../SceneManager/SceneManager.h"

class GameScene : public Scene
{
public:
	GameScene(SDL_Event* e, WindowProperties* windowProperties, SceneManager* sceneManager);

	void update(SDL_Renderer* renderer) override;

private:
	void loadCellData();
	void setBoardStatus();
	void checkForQuitInput();
		
private:
	int m_ScreenWidth, m_ScreenHeight, m_GameBoardWidth, m_GameBoardHeight, m_MouseX, m_MouseY;

	SceneManager* m_SceneManager;
	GameBoard m_GameBoard;
	Camera m_Camera;

	std::jthread m_GameLogicThread;
	std::jthread m_RenderingThread;
};