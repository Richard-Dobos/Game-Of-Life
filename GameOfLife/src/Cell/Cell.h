#pragma once

#include<SDL.h>

class Cell
{
public:
	Cell(int x, int y, bool state);

	SDL_Rect rect;

	int xPos, yPos;
	bool alive = false;

};