#pragma once

#include <tuple>
#include <SDL.h>

#include "../GameBoard/GameBoard.h"
#include "../WindowProperties.h"

class Camera
{
public:
	Camera(int startPosX = 0, int startPosY = 0, GameBoard* gameBoard = nullptr, WindowProperties* windowProperties = nullptr)
		:m_CameraPosX(startPosX), m_CameraPosY(startPosY), m_GameBoard(gameBoard), m_WindowProperties(windowProperties) {}

	void updateCameraPosition(SDL_Event* event);
	void render(SDL_Renderer* renderer);

private:
	std::tuple<int, int> convertFromAbsToRelPos(int x, int y) const;
	bool cameraInCellContext(int x, int y);
	void drawSquare(SDL_Renderer* renderer, SDL_Rect* square, SDL_Color outlineColor, SDL_Color fillColor) const;

private:
	int m_CameraPosX, m_CameraPosY;

	WindowProperties* m_WindowProperties;
	GameBoard* m_GameBoard;
};