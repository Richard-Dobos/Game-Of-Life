#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(SDL_Event* e)
	:Scene(e)
{
	Button StartButton(100, 100, 75, 250, [&]()
		{
			SDL_Color temp = { 255, 0, 0, 255 };

			m_MainButtonColor = temp;
		});
	Button SettingsButton(100, 200, 75, 250, [&]()
		{
			SDL_Color temp = { 0, 255, 0, 255 };

			m_MainButtonColor = temp;
		});
	Button ExitButton(100, 300, 75, 250, [&]()
		{
			SDL_Color temp = { 0, 0, 255, 255 };

			m_MainButtonColor = temp;
		});

	m_Buttons.emplace_back(StartButton);
	m_Buttons.emplace_back(SettingsButton);
	m_Buttons.emplace_back(ExitButton);
}

void MainMenuScene::update(SDL_Renderer* renderer)
{
	for (auto& button : m_Buttons)
	{
		button.renderButton(renderer, &m_MainButtonColor);
	}

	for (auto& button : m_Buttons)
	{
		button.callback(m_Event);
	}
}