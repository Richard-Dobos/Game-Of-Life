#pragma once

#include <tuple>
#include <SDL.h>

#include "../GameBoard/GameBoard.h"
#include "../WindowProperties.h"

class Camera
{
public:
	Camera(GameBoard* gameBoard, WindowProperties* windowProperties);

	void updateCameraPosition(SDL_Event* event);
	void render(SDL_Renderer* renderer);
	
private:
	SDL_Texture* createTexture(SDL_Renderer* renderer);

	void checkForScrollInput(SDL_Event* event);
	void renderSquare(SDL_Renderer* renderer, SDL_Rect* square, SDL_Color outlineColor, SDL_Color fillColor, bool filled) const;

public:
	SDL_Rect m_TextureViewport;
	SDL_Rect m_ViewPort;

private:
	GameBoard* m_GameBoard;
	WindowProperties* m_WindowProperties;

};