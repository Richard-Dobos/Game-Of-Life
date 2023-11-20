#include "Button.h"

void Button::callback(SDL_Event* e)
{
	if(m_IsVisible)
		if (checkForMouseOverButton() && checkMouseButtonClick(e))
			m_Func();
}

bool Button::checkMouseButtonClick(SDL_Event* e) const
{
	if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT)
		return true;

	return false;
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

void Button::renderButton(SDL_Renderer* renderer, SDL_Color* color) const
{
	if (m_IsVisible)
	{
		if (checkForMouseOverButton())
			SDL_SetRenderDrawColor(renderer, color->r * 1.2, color->g * 1.2, color->b * 1.2, color->a);

		else
			SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

		SDL_Rect button(m_xPos, m_yPos, m_Width, m_Height);
		SDL_RenderFillRect(renderer, &button);
	}
}