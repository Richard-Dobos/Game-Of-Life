#pragma once

#include <vector>

#include "SDL.h"
#include "../Scene.h"
#include "../../GameBoard/GameBoard.h"
#include "../../Camera/Camera.h"
#include "../../WindowProperties.h"
#include "../../SceneManager/SceneManager.h"

class GameScene : public Scene
{
public:
	GameScene(SDL_Event* e, WindowProperties* windowProperties, SceneManager* sceneManager);

	void loadCellData();
	void update(SDL_Renderer* renderer) override;

private:
	GameBoard m_GameBoard;
	SceneManager* m_SceneManager;

	int m_ScreenWidth, m_ScreenHeight, m_GameBoardWidth, m_GameBoardHeight, m_MouseX, m_MouseY;
};