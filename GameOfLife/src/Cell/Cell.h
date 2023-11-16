#pragma once

#include<SDL.h>

class Cell
{
public:
	Cell(int x, int y, bool state);

	bool isAlive() const;
	void setAlive(bool state);

	SDL_Rect rect;

	int xPos, yPos;

private:
	bool state = false;
};