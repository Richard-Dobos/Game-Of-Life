#pragma once

#include "../Scene.h"
#include "../../GameBoard/GameBoard.h"
#include "../../Camera/Camera.h"


class GameScene : Scene
{
public:
	void update() override;

private:
	GameBoard gameBoard;

};