#include "Camera.h"

void Camera::render(SDL_Renderer* renderer, GameBoard &gameBoard)
{
	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
	SDL_RenderClear(renderer);


	int aliveCellsSize = gameBoard.getAliveCellVecSize();

	if (aliveCellsSize > 0)
	{
		for (int i = 0; i < aliveCellsSize; i++)
		{
			SDL_Rect* rePTR = &gameBoard.getAliveCell(i)->rect;

			if (cameraInCellContext(rePTR->x, rePTR->y))
			{
			
				rePTR->w = scale;
				rePTR->h = scale;

				std::tie(rePTR->x, rePTR->y) = convertFromAbsToRelPos(gameBoard.getAliveCell(i)->xPos, gameBoard.getAliveCell(i)->yPos);
				
				drawSquare(renderer, rePTR, SDL_Color(0, 142, 10, 255), SDL_Color(0, 100, 5, 255));
			}
		}
	}

	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
	SDL_RenderPresent(renderer);
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

	relativePosX = x * scale - currentPosX;
	relativePosY = y * scale - currentPosY;

	return std::make_tuple(relativePosX, relativePosY);
}

bool Camera::cameraInCellContext(int x, int y)
{
	return x + scale >= currentPosX && x <= currentPosX + screenWidth && y + scale >= currentPosY && y <= currentPosY + screenHeight ? true : false;
}