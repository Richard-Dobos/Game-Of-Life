#pragma once

#include <tuple>
#include <SDL.h>

#include "../WindowProperties.h"
#include "../GameBoard/GameBoard.h"

class Camera
{
public:
	Camera(GameBoard* gameBoard, WindowProperties* windowProperties);

	void render(SDL_Renderer* renderer);
	bool updateCameraPosition(SDL_Event* event);
	
private:
	SDL_Texture* createTexture(SDL_Renderer* renderer);

	bool checkForScrollInput(SDL_Event* event);

public:
	SDL_Rect m_ViewPort;
	SDL_Rect m_TextureViewport;

private:
	GameBoard* m_GameBoard;
	WindowProperties* m_WindowProperties;
};