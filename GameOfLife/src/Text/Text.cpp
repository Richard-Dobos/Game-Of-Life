#include "Text.h"

Text::Text(int x, int y, int width, int height, int fontSize, std::string text, std::string fontPath, SDL_Color* textColor)
	:m_FontSize(fontSize), m_Text(text), m_FontPath(fontPath), m_TextColor(textColor)
{
	m_TextBox.x = x;
	m_TextBox.y = y;
	m_TextBox.w = width;
	m_TextBox.h = height;

	m_Font = TTF_OpenFont(m_FontPath.c_str(), m_FontSize);

	if (!m_Font)	std::cout << "\nCouldn't find font in specified path.";
}

void Text::renderText(SDL_Renderer* renderer)
{
	SDL_Texture* textTexture = createTextTexture(renderer);
	
	SDL_RenderCopy(renderer, textTexture, nullptr, &m_TextBox);
	SDL_DestroyTexture(textTexture);
}

SDL_Texture* Text::createTextTexture(SDL_Renderer* renderer)
{
	SDL_Texture* textTexture;
	SDL_Surface* text;

	text = TTF_RenderText_Solid(m_Font, m_Text.c_str(), *m_TextColor);
	textTexture = SDL_CreateTextureFromSurface(renderer, text);

	SDL_FreeSurface(text);

	return textTexture;
}