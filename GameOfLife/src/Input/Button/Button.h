#pragma once

#include <SDL.h>
#include <string>
#include <iostream>
#include <functional>

#include "../../Text/Text.h"

class Button
{
public:
	Button(int xPos, int yPos, int height, int width, const SDL_Color& buttonColor, const SDL_Color& hoverColor, Text text, std::function<void()> func)
		: m_xPos(xPos), m_yPos(yPos), m_Height(height), m_Width(width), m_Text(text), m_ButtonColor(buttonColor), m_HoverColor(hoverColor), m_Func(func) {}

	void callback(SDL_Event* e);
	void renderButton(SDL_Renderer* renderer);

public:
	bool m_IsVisible = true;

private:
	bool checkForMouseOverButton() const;
	bool checkMouseButtonClick(SDL_Event* e) const;

private:
	int m_xPos, m_yPos, m_Height, m_Width;

	Text m_Text;
	SDL_Color m_ButtonColor;
	SDL_Color m_HoverColor;
	std::function<void()> m_Func = nullptr;
};