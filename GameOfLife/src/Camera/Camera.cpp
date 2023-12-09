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

bool Camera::updateCameraPosition(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		int cameraMoveMagnitude = m_TextureViewport.w / 7;

		std::cout << std::format("\nTexture Viewport\nX: {} | Y: {}\nWidth: {} | Height: {}", m_TextureViewport.x , m_TextureViewport.y, m_TextureViewport.w, m_TextureViewport.h);

		switch (event->key.keysym.sym)
		{
		case SDLK_w:
			if (m_TextureViewport.y - cameraMoveMagnitude < 0)
				m_TextureViewport.y = 0;
			else
				m_TextureViewport.y -= cameraMoveMagnitude;

			return true;
			break;

		case SDLK_s:
			if (m_TextureViewport.y + m_TextureViewport.h + cameraMoveMagnitude > m_GameBoard->m_GameBoardHeight)
				m_TextureViewport.y = m_GameBoard->m_GameBoardHeight - m_TextureViewport.h;

			else
				m_TextureViewport.y += cameraMoveMagnitude;

			return true;
			break;

		case SDLK_a:
			if (m_TextureViewport.x - cameraMoveMagnitude < 0)
				m_TextureViewport.x = 0;
			else
				m_TextureViewport.x -= cameraMoveMagnitude;

			return true;
			break;

		case SDLK_d:
			if (m_TextureViewport.x + m_TextureViewport.w + cameraMoveMagnitude > m_GameBoard->m_GameBoardWidth)
				m_TextureViewport.x = m_GameBoard->m_GameBoardWidth - m_TextureViewport.w;

			else
				m_TextureViewport.x += cameraMoveMagnitude;

			return true;
			break;
		}
	}

	return checkForScrollInput(event) != false ? true : false;
}

SDL_Texture* Camera::createTexture(SDL_Renderer* renderer)
{
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, m_TextureViewport.x + m_TextureViewport.w, m_TextureViewport.y + m_TextureViewport.h);

	SDL_SetRenderTarget(renderer, texture);

	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 142, 10, 255);

	for (const auto aliveCell : m_GameBoard->m_AliveCells)
	{
		const auto [x, y] = aliveCell.second;

		if(x >= m_TextureViewport.x && x <= m_TextureViewport.x + m_TextureViewport.w &&
			y >= m_TextureViewport.y && y <= m_TextureViewport.y + m_TextureViewport.h)
			SDL_RenderDrawPoint(renderer, x, y);
	}

	SDL_SetRenderTarget(renderer, nullptr);

	return texture;
}
	
bool Camera::checkForScrollInput(SDL_Event* event)
{
	if (event->type == SDL_MOUSEWHEEL)
	{
		if (event->wheel.y > 0)
		{
			if (m_GameBoard->scale * 2 < 129)
			{
				m_TextureViewport.w /= 2;
				m_TextureViewport.h /= 2;
				m_GameBoard->scale *= 2;
			}

			return true;
		}

		if (event->wheel.y < 0)
		{
			if (m_GameBoard->scale / 2 > 1)
			{
				m_TextureViewport.w *= 2;
				m_TextureViewport.h *= 2;
				m_GameBoard->scale /= 2;

				return true;
			}
		}
	}

	return false;
}
