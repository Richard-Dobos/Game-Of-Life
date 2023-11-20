#include "Cell.h"

Cell::Cell(int xPos, int yPos, bool state)
	: xPos(xPos), yPos(yPos), alive(state)
{
	rect = SDL_Rect(xPos, yPos);
}