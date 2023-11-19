#include "GameScene.h"

void GameScene::update(SDL_Renderer* renderer)
{
	m_Camera.render(renderer);
	m_GameBoard.update();
}