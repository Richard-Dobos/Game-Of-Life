#pragma once

#include <SDL.h>
#include <iostream>
#include <functional>

class Button
{
public:
	Button(int xPos, int yPos, int height, int width, std::function<void()> func)
		:m_Func(func), m_xPos(xPos), m_yPos(yPos), m_Height(height), m_Width(width) {}

	void callback(SDL_Event* e);
	void renderButton(SDL_Renderer* renderer, SDL_Color* color) const;

private:
	bool checkForMouseOverButton() const;
	bool checkMouseButtonClick(SDL_Event* e) const;

private:
	std::function<void()> m_Func = []() { std::cout << "\nNO FUNCTION ASSIGNED!\n"; };

	int m_xPos, m_yPos, m_Height, m_Width;
};