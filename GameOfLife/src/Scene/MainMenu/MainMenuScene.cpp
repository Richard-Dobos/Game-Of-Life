#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(SDL_Event* e, WindowProperties* windowProperties, SceneManager* sceneManager)
	:Scene(e, windowProperties), m_SceneManager(sceneManager)
{
	m_Buttons.emplace_back(m_WindowProperties->windowWidth / 2 - (250 / 4), 100, 75, 250, m_ButtonColor, m_ButtonColorHover, [&]()
		{	
			m_SceneManager->changeScene<GameScene>();
		});

	m_Buttons.emplace_back(m_WindowProperties->windowWidth / 2 - (250 / 4), 200, 75, 250, m_ButtonColor, m_ButtonColorHover, [&]()
		{
			m_SceneManager->changeScene<EditorScene>();
		});

	m_Buttons.emplace_back(m_WindowProperties->windowWidth / 2 - (250 / 4), 300, 75, 250, m_ButtonColor, m_ButtonColorHover, [&]()
		{
			m_WindowProperties->exit = true;
			SDL_Quit();
		});
}

void MainMenuScene::update(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
	SDL_RenderClear(renderer);

	for (auto& button : m_Buttons)
	{
		button.renderButton(renderer);
	}

	for (auto& button : m_Buttons)
	{
		button.callback(m_Event);
	}
}