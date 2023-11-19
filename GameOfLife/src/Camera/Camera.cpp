#include "Camera.h"

void Camera::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
	SDL_RenderClear(renderer);

	int aliveCellsSize = m_GameBoard->getAliveCellVecSize();

	if (aliveCellsSize > 0)
	{
		for (int i = 0; i < aliveCellsSize; i++)
		{
			SDL_Rect* rePTR = &m_GameBoard->getAliveCell(i)->rect;

			if (cameraInCellContext(rePTR->x, rePTR->y))
			{
				rePTR->w = m_GameBoard->scale;
				rePTR->h = m_GameBoard->scale;

				auto [x, y] = convertFromAbsToRelPos(m_GameBoard->getAliveCell(i)->xPos, m_GameBoard->getAliveCell(i)->yPos);

				rePTR->x = x;
				rePTR->y = y;

				drawSquare(renderer, rePTR, SDL_Color(0, 142, 10, 255), SDL_Color(0, 100, 5, 255));
			}
		}
	}

	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
	SDL_RenderPresent(renderer);
}

void Camera::updateCameraPosition(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		int cameraMoveMagnitude = m_GameBoard->scale * 10;

		switch (event->key.keysym.sym)
		{
		case SDLK_w:
			if (m_CameraPosY - cameraMoveMagnitude < 0)
				m_CameraPosY = 0;
			else
				m_CameraPosY -= cameraMoveMagnitude;
			break;

		case SDLK_s:
			if (m_CameraPosY + cameraMoveMagnitude > m_GameBoard->m_GameBoardHeight)
				m_CameraPosY = m_GameBoard->m_GameBoardHeight - m_WindowProperties->windowHeight;
			else
				m_CameraPosY += cameraMoveMagnitude;
			break;

		case SDLK_a:
			if (m_CameraPosX - cameraMoveMagnitude < 0)
				m_CameraPosX = 0;
			else
				m_CameraPosX -= cameraMoveMagnitude;
			break;

		case SDLK_d:
			if (m_CameraPosX + cameraMoveMagnitude > m_GameBoard->m_GameBoardWidth)
				m_CameraPosX = m_GameBoard->m_GameBoardWidth - m_WindowProperties->windowWidth;
			else
				m_CameraPosX += cameraMoveMagnitude;

			break;
		}
	}
}
	
void Camera::drawSquare(SDL_Renderer* renderer, SDL_Rect* square, SDL_Color outlineColor, SDL_Color fillColor) const
{
	SDL_SetRenderDrawColor(renderer, 0, 142, 10, 255);
	SDL_RenderFillRect(renderer, square);

	SDL_SetRenderDrawColor(renderer, 0, 100, 5, 255);
	SDL_RenderDrawRect(renderer, square);
}

std::tuple<int, int> Camera::convertFromAbsToRelPos(int x, int y) const
{
	int relativePosX = 0;
	int relativePosY = 0;

	relativePosX = (x - m_CameraPosX) * m_GameBoard->scale;
	relativePosY = (y - m_CameraPosY) * m_GameBoard->scale;

	return std::make_tuple(relativePosX, relativePosY);
}

bool Camera::cameraInCellContext(int x, int y)
{
	return x + m_GameBoard->scale >= m_CameraPosX && x <= m_CameraPosX + m_WindowProperties->windowWidth && y + m_GameBoard->scale >= m_CameraPosY && y <= m_CameraPosY + m_WindowProperties->windowHeight ? true : false;
}