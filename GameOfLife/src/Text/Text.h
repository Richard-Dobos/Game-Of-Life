#pragma once

#include <SDL.h>
#include <string>
#include <iostream>
#include <SDL_ttf.h>

class Text
{
public:
	Text(int x, int y, int width, int height, int fontSize,std::string text, std::string fontPath, SDL_Color* textColor);

	void renderText(SDL_Renderer* renderer);

	SDL_Texture* createTextTexture(SDL_Renderer* renderer);

private:
	int m_FontSize;

	std::string m_Text;
	std::string m_FontPath;

	TTF_Font* m_Font;
	SDL_Rect m_TextBox;
	SDL_Color* m_TextColor;
};
