#pragma once

#include <tuple>
#include "SDL.h"
#include "../GameBoard/GameBoard.h"

class Camera
{
public:
	Camera(int screenWidth = 0, int screenHeight = 0, int startPosX = 0, int startPosY = 0)
		:screenWidth(screenWidth), screenHeight(screenHeight), currentPosX(startPosX), currentPosY(startPosY) {}

	void updateCameraPosition();
	void render(SDL_Renderer* renderer, GameBoard &gameBoard);
	
private:
	std::tuple<int, int> convertFromAbsToRelPos(int x, int y) const;
	bool cameraInCellContext(int x, int y);
	void drawSquare(SDL_Renderer* renderer, SDL_Rect* square, SDL_Color outlineColor, SDL_Color fillColor) const;

	int screenWidth, screenHeight, currentPosX, currentPosY;
	int scale = 20;
};