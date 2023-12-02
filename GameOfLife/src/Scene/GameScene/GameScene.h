#pragma once

#include <vector>

#include "SDL.h"
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
	
private:
	bool m_Changed = true;
	int m_ScreenWidth, m_ScreenHeight, m_GameBoardWidth, m_GameBoardHeight, m_MouseX, m_MouseY;

	SceneManager* m_SceneManager;
	GameBoard m_GameBoard;
	Camera m_Camera;
};