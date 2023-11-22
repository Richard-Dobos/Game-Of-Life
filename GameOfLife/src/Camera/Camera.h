#pragma once

#include <tuple>
#include <SDL.h>

#include "../GameBoard/GameBoard.h"
#include "../WindowProperties.h"

class Camera
{
public:
	Camera(GameBoard* gameBoard = nullptr, WindowProperties* windowProperties = nullptr)
		:m_GameBoard(gameBoard), m_WindowProperties(windowProperties) {}

	void updateCameraPosition(SDL_Event* event);
	void render(SDL_Renderer* renderer);
	
private:
	std::tuple<int, int> convertFromAbsToRelPos(int x, int y) const;
	
	bool cameraInCellContext(int x, int y);
	
	void checkForScrollInput(SDL_Event* event);
	void renderSquare(SDL_Renderer* renderer, SDL_Rect* square, SDL_Color outlineColor, SDL_Color fillColor, bool filled) const;

public:
	int m_CameraPosX = 0;
	int m_CameraPosY = 0;

private:

	GameBoard* m_GameBoard;
	WindowProperties* m_WindowProperties;
};