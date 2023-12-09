#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(SDL_Event* e, WindowProperties* windowProperties, SceneManager* sceneManager)
	:Scene(e, windowProperties, sceneManager->m_SaveManager), m_SceneManager(sceneManager)
{
	int buttonX = m_WindowProperties->windowWidth / 2 - (250 / 4);
	int buttonY = 100; 
	int buttonH = 75;
	int buttonW = 250;

	int buttonTextX = buttonX + (buttonW * 0.1f);
	int buttonTextW = buttonW * 0.8f;

	std::string fontPath = m_SaveManager->m_AbsolutePath + "/Fonts/Open24Display.ttf";

	m_Buttons.emplace_back(buttonX, buttonY, buttonH, buttonW, m_ButtonColor, m_ButtonColorHover, 
		Text(buttonTextX, buttonY, buttonTextW, buttonH, 50, "Start", fontPath, &m_ButtonTextColor),
		[&]()
		{	
			m_SceneManager->changeScene<GameScene>();
		});

	m_Buttons.emplace_back(buttonX, buttonY * 2, buttonH, buttonW, m_ButtonColor, m_ButtonColorHover, 
		Text(buttonTextX, buttonY * 2, buttonTextW, buttonH, 50, "Editor", fontPath, &m_ButtonTextColor),
		[&]()
		{
			m_SceneManager->changeScene<EditorScene>();
		});

	m_Buttons.emplace_back(buttonX, buttonY * 3, buttonH, buttonW, m_ButtonColor, m_ButtonColorHover, 
		Text(buttonTextX, buttonY * 3, buttonTextW, buttonH, 50, "Quit", fontPath, &m_ButtonTextColor),
		[&]()
		{
			m_WindowProperties->exit = true;
			SDL_Quit();
		});
	
	std::cout << "\nAbsolute path: " << m_SaveManager->m_AbsolutePath;

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