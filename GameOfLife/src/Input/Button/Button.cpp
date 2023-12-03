#include "Button.h"

void Button::callback(SDL_Event* e)
{
	if(m_IsVisible)
		if (checkForMouseOverButton() && checkMouseButtonClick(e))
			m_Func();
}

void Button::renderButton(SDL_Renderer* renderer)
{
	if (m_IsVisible)
	{
		if (checkForMouseOverButton())
			SDL_SetRenderDrawColor(renderer, m_HoverColor.r, m_HoverColor.g, m_HoverColor.b, m_HoverColor.a);

		else
			SDL_SetRenderDrawColor(renderer, m_ButtonColor.r, m_ButtonColor.g, m_ButtonColor.b, m_ButtonColor.a);

		SDL_Rect button(m_xPos, m_yPos, m_Width, m_Height);
		SDL_RenderFillRect(renderer, &button);
		m_Text.renderText(renderer);
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