#include "EditorScene.h"

EditorScene::EditorScene(SDL_Event* e, WindowProperties* windowProperties)
	:Scene(e, windowProperties) 
{
	int buttonPosX = m_BoardSettingsPosX + ((m_WindowProperties->windowWidth - m_BoardSettingsPosX) * 0.25f);
	int buttonPosY = m_WindowProperties->windowHeight * 0.33f;
	int buttonHeight = m_WindowProperties->windowHeight * 0.05f;
	int buttonWidth = (m_WindowProperties->windowWidth - (m_WindowProperties->windowWidth - m_WindowProperties->windowWidth * 0.15f)) * 0.5f;
	float offset = 0.1f * m_WindowProperties->windowHeight;

	m_Buttons.emplace_back(buttonPosX, buttonPosY, buttonHeight, buttonWidth, [&]()
		{
				m_GameBoard.m_GameBoardHeight = 4096;
				m_GameBoard.m_GameBoardWidth = 4096;
		});

	m_Buttons.emplace_back(buttonPosX, buttonPosY + offset, buttonHeight, buttonWidth, [&]()
		{
			m_GameBoard.m_GameBoardHeight = 2048;
			m_GameBoard.m_GameBoardWidth = 2048;
		});

	m_Buttons.emplace_back(buttonPosX, buttonPosY + 2 * offset, buttonHeight, buttonWidth, [&]()
		{
			m_GameBoard.m_GameBoardHeight = 1024;
			m_GameBoard.m_GameBoardWidth = 1024;
		});
}

void EditorScene::update(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 130);
	SDL_RenderClear(renderer);
	
	checkForSettingsShortcut();
	renderBoardSettingsMenu(renderer);

	for (Button button : m_Buttons)
	{
		button.renderButton(renderer, &m_ButtonColor);
		button.callback(m_Event);
	}
}

void EditorScene::renderBoardSettingsMenu(SDL_Renderer* renderer)
{
	if (!m_RenderBoardSettings)
		return;

	SDL_Rect boardSettingsBackground = {m_BoardSettingsPosX, 0, m_WindowProperties->windowWidth * 0.15f, m_WindowProperties->windowHeight};

	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 100);
	SDL_RenderFillRect(renderer, &boardSettingsBackground);
	

}

void EditorScene::checkForSettingsShortcut()
{
	if(m_Event->type == SDL_KEYDOWN)
	{ 
		if (m_Event->key.keysym.sym = SDLK_t)
		{
			m_RenderBoardSettings = !m_RenderBoardSettings;
			
			for (Button& button : m_Buttons)
				button.m_IsVisible = m_RenderBoardSettings;

		}
	}
}