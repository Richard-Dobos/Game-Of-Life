#include "GameScene.h"

GameScene::GameScene(int screenWidth, int screenHeight, int gameBoardWidth, int gameBoardHeight)
	:gameBoard(gameBoardHeight, gameBoardWidth), camera(screenWidth, screenHeight), screenWidth(screenWidth), screenHeight(screenHeight), gameBoardWidth(gameBoardWidth), gameBoardHeight(gameBoardHeight)
{

}

void GameScene::update(SDL_Renderer* renderer)
{
	camera.render(renderer, gameBoard);
	gameBoard.printBoard();
	gameBoard.update();
}