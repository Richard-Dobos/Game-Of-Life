#include "Button.h"

Button::Button(int xPos, int yPos, int height, int width, const SDL_Color& buttonColor, const SDL_Color& hoverColor, std::function<void()> func)
	:m_ButtonColor(buttonColor), m_HoverColor(hoverColor), m_Func(func), m_xPos(xPos), m_yPos(yPos), m_Height(height), m_Width(width)
{
}

void Button::callback(SDL_Event* e)
{
	if(m_IsVisible)
		if (checkForMouseOverButton() && checkMouseButtonClick(e))
			m_Func();
}

void Button::renderButton(SDL_Renderer* renderer) const
{
	if (m_IsVisible)
	{
		if (checkForMouseOverButton())
			SDL_SetRenderDrawColor(renderer, m_HoverColor.r, m_HoverColor.g, m_HoverColor.b, m_HoverColor.a);

		else
			SDL_SetRenderDrawColor(renderer, m_ButtonColor.r, m_ButtonColor.g, m_ButtonColor.b, m_ButtonColor.a);

		SDL_Rect button(m_xPos, m_yPos, m_Width, m_Height);
		SDL_RenderFillRect(renderer, &button);
	}
}

bool Button::checkForMouseOverButton() const
{
	int xMousePos, yMousePos;

	SDL_GetMouseState(&xMousePos, &yMousePos);

	if (xMousePos >= m_xPos && xMousePos <= m_xPos + m_Width
		&& yMousePos >= m_yPos && yMousePos <= m_yPos + m_Height)
		return true;

	return false;
}

bool Button::checkMouseButtonClick(SDL_Event* e) const
{
	if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT)
		return true;

	return false;
}