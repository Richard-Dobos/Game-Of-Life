#include "Cell.h"

Cell::Cell(int xPos, int yPos, bool state)
	: xPos(xPos), yPos(yPos), state(state)
{
	rect = SDL_Rect(xPos, yPos);
}

bool Cell::isAlive() const
{
	return state;
}

void Cell::setAlive(bool state)
{
	Cell::state = state;
}