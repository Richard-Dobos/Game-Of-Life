#pragma once

#include <SDL.h>
#include <string>
#include <iostream>
#include <functional>

class Button
{
public:
	Button(int xPos, int yPos, int height, int width, const SDL_Color& buttonColor, const SDL_Color& hoverColor, std::function<void()> func);

	void callback(SDL_Event* e);
	void renderButton(SDL_Renderer* renderer) const;

public:
	bool m_IsVisible = true;

private:
	bool checkForMouseOverButton() const;
	bool checkMouseButtonClick(SDL_Event* e) const;

private:
	int m_xPos, m_yPos, m_Height, m_Width;

	SDL_Color m_ButtonColor;
	SDL_Color m_HoverColor;
	std::function<void()> m_Func = nullptr;
};