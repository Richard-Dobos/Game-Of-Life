#include "EditorScene.h"

EditorScene::EditorScene(SDL_Event* e, WindowProperties* windowProperties, SceneManager* sceneManager)
	:Scene(e, windowProperties), m_Camera(&m_GameBoard, windowProperties), m_SceneManager(sceneManager)
{
	int buttonPosX = m_BoardSettingsPosX + ((m_WindowProperties->windowWidth - m_BoardSettingsPosX) * 0.25f);
	int buttonPosY = m_WindowProperties->windowHeight * 0.33f;
	int buttonHeight = m_WindowProperties->windowHeight * 0.05f;
	int buttonWidth = (m_WindowProperties->windowWidth - (m_WindowProperties->windowWidth - m_WindowProperties->windowWidth * 0.15f)) * 0.5f;
	float offset = 0.1f * m_WindowProperties->windowHeight;


	//Main Menu Button
	m_Buttons.emplace_back(buttonPosX, buttonPosY, buttonHeight, buttonWidth, m_ButtonColor, m_ButtonColorHover, [&]()
		{
			m_SceneManager->changeScene<MainMenuScene>();
		});

	//Save Button
	m_Buttons.emplace_back(buttonPosX, buttonPosY + offset, buttonHeight, buttonWidth, m_ButtonColor, m_ButtonColorHover, [&]()
		{
			saveCellData();
		});

	//Reset Board Button
	m_Buttons.emplace_back(buttonPosX, buttonPosY + 2 * offset, buttonHeight, buttonWidth, m_ButtonColor, m_ButtonColorHover, [&]()
		{
			m_GameBoard.resetBoard();
		});
}

void EditorScene::update(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 130);
	SDL_RenderClear(renderer);

	m_Camera.render(renderer);
	m_Camera.updateCameraPosition(m_Event);
	renderBoardSettingsMenu(renderer);
	
	for (Button button : m_Buttons)
	{
		button.renderButton(renderer);
		button.callback(m_Event);
	}

	checkForSettingsShortcut();
	addLiveCell();
}

void EditorScene::renderBoardSettingsMenu(SDL_Renderer* renderer) const 
{
	if (!m_RenderBoardSettings)
		return;

	SDL_Rect boardSettingsBackground = {m_BoardSettingsPosX, 0, m_WindowProperties->windowWidth * 0.15f, m_WindowProperties->windowHeight};

	SDL_SetRenderDrawColor(renderer, 35, 35, 35, 255);
	SDL_RenderFillRect(renderer, &boardSettingsBackground);
}

void EditorScene::checkForSettingsShortcut()
{
	if(m_Event->type == SDL_KEYDOWN)
	{ 
		if (m_Event->key.keysym.sym == SDLK_t)
		{
			m_RenderBoardSettings = !m_RenderBoardSettings;
			
			for (Button& button : m_Buttons)
				button.m_IsVisible = m_RenderBoardSettings;
		}
	}
}

void EditorScene::addLiveCell()
{
	if (m_Event->type == SDL_MOUSEBUTTONDOWN && m_Event->button.button == SDL_BUTTON_LEFT)
	{
		int mouseX, mouseY;

		SDL_GetMouseState(&mouseX, &mouseY);

		int gridX = floor(mouseX / (m_WindowProperties->windowWidth / m_Camera.m_TextureViewport.w) + m_Camera.m_TextureViewport.x);
		int gridY = floor(mouseY / (m_WindowProperties->windowHeight / m_Camera.m_TextureViewport.h) + m_Camera.m_TextureViewport.y);

		int absX = (gridY * m_GameBoard.m_GameBoardWidth) + gridY + gridX;

		if (m_RenderBoardSettings)
		{
			if (mouseX < m_BoardSettingsPosX)
			{
				if (m_GameBoard.m_AliveCells.contains(absX + gridY))
				{
					m_GameBoard.m_AliveCells.erase(absX + gridY);
					m_GameBoard.m_CellsData[gridY][gridX] = false;
				}

				else
				{
					m_GameBoard.m_AliveCells[absX + gridY] = std::make_tuple(gridX, gridY);
					m_GameBoard.m_CellsData[gridY][gridX] = true;
				}
				
			}
		}

		else
		{
			if (m_GameBoard.m_AliveCells.contains(absX + gridY))
			{
				m_GameBoard.m_AliveCells.erase(absX + gridY);
				m_GameBoard.m_CellsData[gridY][gridX] = false;
			}

			else
			{
				m_GameBoard.m_AliveCells[absX + gridY] = std::make_tuple(gridX, gridY);
				m_GameBoard.m_CellsData[gridY][gridX] = true;
			}
		}
	}
}

void EditorScene::saveCellData()
{
	m_FileManager->createSaveCategory("CellData");

	for (const auto cell : m_GameBoard.m_AliveCells)
	{
		const auto& [x, y] = cell.second;

		std::string save = std::format("{},{}", x, y);

		std::cout << "\n" << save;

		m_FileManager->addToBuffer("Cell",save);
	}

	m_FileManager->saveToFileFromSaveBuffer();
	m_FileManager->clearSaveBuffer();
}