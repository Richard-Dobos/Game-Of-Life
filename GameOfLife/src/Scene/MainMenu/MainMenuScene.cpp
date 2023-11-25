#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(SDL_Event* e, WindowProperties* windowProperties)
	:Scene(e, windowProperties)
{
	m_Buttons.emplace_back(100, 100, 75, 250, [&]()
		{	
			SDL_Color temp = { 255, 0, 0, 255 };

			m_MainButtonColor = temp;
		});

	m_Buttons.emplace_back(100, 200, 75, 250, [&]()
		{
			SDL_Color temp = { 0, 255, 0, 255 };

			m_MainButtonColor = temp;
		});

	m_Buttons.emplace_back(100, 300, 75, 250, [&]()
		{
			SDL_Color temp = { 0, 0, 255, 255 };

			m_MainButtonColor = temp;
		});
}

void MainMenuScene::update(SDL_Renderer* renderer)
{
	for (auto& button : m_Buttons)
	{
		button.renderButton(renderer, &m_MainButtonColor, &m_MainButtonColorHover);
	}

	for (auto& button : m_Buttons)
	{
		button.callback(m_Event);
	}
}