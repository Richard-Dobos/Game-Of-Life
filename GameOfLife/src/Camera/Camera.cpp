#include "Camera.h"

Camera::Camera(GameBoard* gameBoard, WindowProperties* windowProperties)
:m_GameBoard(gameBoard), m_WindowProperties(windowProperties) 
{
	m_ViewPort.x = 0;
	m_ViewPort.y = 0;
	m_TextureViewport.x = 0;
	m_TextureViewport.y = 0;

	m_ViewPort.w = m_WindowProperties->windowWidth;
	m_ViewPort.h = m_WindowProperties->windowHeight;

	m_TextureViewport.w = m_WindowProperties->windowWidth / m_GameBoard->scale;
	m_TextureViewport.h = m_WindowProperties->windowHeight / m_GameBoard->scale;
}

void Camera::render(SDL_Renderer* renderer)
{
	SDL_Texture* texture = createTexture(renderer);
	
	SDL_RenderCopy(renderer, texture, &m_TextureViewport, &m_ViewPort);
	
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
}

SDL_Texture* Camera::createTexture(SDL_Renderer* renderer)
{
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, m_WindowProperties->windowWidth, m_WindowProperties->windowHeight);

	SDL_SetRenderTarget(renderer, texture);

	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
	SDL_RenderClear(renderer);

	for (std::tuple<int, int> aliveCell : m_GameBoard->aliveCells)
	{
		const auto [x, y] = aliveCell;

		SDL_SetRenderDrawColor(renderer, 0, 142, 10, 255);

		SDL_RenderDrawPoint(renderer, x, y);

	}

	SDL_SetRenderTarget(renderer, nullptr);

	return texture;
}

void Camera::updateCameraPosition(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		int cameraMoveMagnitude = m_TextureViewport.w / 7;

		switch (event->key.keysym.sym)
		{
		case SDLK_w:
			if (m_TextureViewport.y - cameraMoveMagnitude < 0)
				m_TextureViewport.y = 0;
			else
				m_TextureViewport.y -= cameraMoveMagnitude;
			break;

		case SDLK_s:
			if (m_TextureViewport.y + cameraMoveMagnitude > m_GameBoard->m_GameBoardHeight)
				m_TextureViewport.y = m_GameBoard->m_GameBoardHeight - m_WindowProperties->windowHeight;
			else
				m_TextureViewport.y += cameraMoveMagnitude;
			break;

		case SDLK_a:
			if (m_TextureViewport.x - cameraMoveMagnitude < 0)
				m_TextureViewport.x = 0;
			else
				m_TextureViewport.x -= cameraMoveMagnitude;
			break;

		case SDLK_d:
			if (m_TextureViewport.x + cameraMoveMagnitude > m_GameBoard->m_GameBoardWidth)
				m_TextureViewport.x = m_GameBoard->m_GameBoardWidth - m_WindowProperties->windowWidth;
			else
				m_TextureViewport.x += cameraMoveMagnitude;
			break;
		}
	}

	checkForScrollInput(event);
}
	
void Camera::checkForScrollInput(SDL_Event* event)
{
	if (event->type == SDL_MOUSEWHEEL)
	{
		if (event->wheel.y > 0)
		{
			m_TextureViewport.w /= 2;
			m_TextureViewport.h /= 2;
			m_GameBoard->scale *= 2;
		}

		if (event->wheel.y < 0)
		{
			if (m_GameBoard->scale > 1)
			{
				m_TextureViewport.w *= 2;
				m_TextureViewport.h *= 2;
				m_GameBoard->scale /= 2;
			}
		}
	}
}

void Camera::renderSquare(SDL_Renderer* renderer, SDL_Rect* square, SDL_Color outlineColor, SDL_Color fillColor, bool filled) const
{
	if (filled)
	{
		SDL_SetRenderDrawColor(renderer, 0, 142, 10, 255);
		SDL_RenderFillRect(renderer, square);
	}

	SDL_SetRenderDrawColor(renderer, 0, 100, 5, 255);
	SDL_RenderDrawRect(renderer, square);
}