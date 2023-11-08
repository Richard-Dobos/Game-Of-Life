#include "GameScene.h"

void GameScene::initScene(int screenWidth, int screenHeight, int gameBoardWidth, int gameBoardHeight)
{
	m_ScreenWidth = screenWidth;
	m_ScreenHeight = screenHeight;
	m_GameBoardWidth = gameBoardWidth;
	m_GameBoardHeight = gameBoardHeight;
}


void GameScene::update(SDL_Renderer* renderer)
{
	m_Camera.render(renderer, m_GameBoard);
	m_GameBoard.update();
}