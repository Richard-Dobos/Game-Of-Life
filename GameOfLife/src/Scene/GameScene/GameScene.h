#pragma once

#include <vector>

#include "SDL.h"
#include "../../GameBoard/GameBoard.h"
#include "../../Camera/Camera.h"


class GameScene
{
public:
	GameScene(int screenWidth, int screenHeight, int gameBoardWidth, int gameBoardHeight);

	void update(SDL_Renderer* renderer);

private:
	GameBoard gameBoard;
	Camera camera;

	int screenWidth, screenHeight, gameBoardWidth, gameBoardHeight;
};	