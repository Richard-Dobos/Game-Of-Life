#pragma once

#include <SDL.h>

class Button
{
public:
	Button(const SDL_Event* Event, int xPos, int yPos, int height, int width)
		:m_event(Event), m_xPos(xPos), m_yPos(yPos), m_height(height), m_width(width) {}

	void onClick();

private:
	const SDL_Event* m_event;
	int m_xPos, m_yPos, m_height, m_width;
};