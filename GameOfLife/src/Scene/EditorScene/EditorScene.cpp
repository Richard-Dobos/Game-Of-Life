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
	m_Buttons.emplace_back(buttonPosX, buttonPosY, buttonHeight, buttonWidth, [&]()
		{
			m_SceneManager->changeScene<MainMenuScene>();
		});

	//Save Button
	m_Buttons.emplace_back(buttonPosX, buttonPosY + offset, buttonHeight, buttonWidth, [&]()
		{
			saveCellData();
		});

	//Reset Button
	m_Buttons.emplace_back(buttonPosX, buttonPosY + 2 * offset, buttonHeight, buttonWidth, [&]()
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

	checkForSettingsShortcut();
	renderBoardSettingsMenu(renderer);

	addLiveCell();

	for (Button button : m_Buttons)
	{
		button.renderButton(renderer, &m_ButtonColor, &m_ButtonHoverColor);
		button.callback(m_Event);
	}
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

void EditorScene::saveCellData()
{
	m_FileManager->createSaveCategory("CellData");

	for (const auto cell : m_GameBoard.aliveCells)
	{
		const auto& [x, y] = cell;

		std::string save = std::format("{},{}", x, y);

		m_FileManager->addToBuffer("Cell",save);
	}

	m_FileManager->saveToFileFromSaveBuffer();
	m_FileManager->clearSaveBuffer();
}

void EditorScene::addLiveCell()
{
	if (m_Event->type == SDL_MOUSEBUTTONDOWN)
	{
		int MouseX, MouseY;

		SDL_GetMouseState(&MouseX, &MouseY);

		if (m_Event->button.button == SDL_BUTTON_LEFT)
		{
			int x = floor(MouseX / (m_WindowProperties->windowWidth / m_Camera.m_TextureViewport.w) + m_Camera.m_TextureViewport.x);
			int y = floor(MouseY / (m_WindowProperties->windowHeight / m_Camera.m_TextureViewport.h) + m_Camera.m_TextureViewport.y);

			std::cout << std::format("\nScaleX: {}\nScaleY: {}\nMouseX: {} | MouseY: {}\nX: {} | Y: {}", m_Camera.m_TextureViewport.w, m_Camera.m_TextureViewport.h,MouseX, MouseY, x, y);
			std::cout << std::format("\nTexture Size: {} : {}\nViewport Size: {} : {}\nTexture View Position: {} : {}", 
				m_Camera.m_TextureViewport.w, m_Camera.m_TextureViewport.h, m_Camera.m_ViewPort.w, m_Camera.m_ViewPort.h, m_Camera.m_TextureViewport.x, m_Camera.m_TextureViewport.y);


			if (m_RenderBoardSettings)
			{
				if(MouseX < m_BoardSettingsPosX)
				{
					m_GameBoard.aliveCells.emplace_back(std::make_tuple(x, y));
					m_GameBoard.m_CellsData[y][x] = !m_GameBoard.m_CellsData[y][x];
				}
			}

			else
			{
				m_GameBoard.aliveCells.emplace_back(std::make_tuple(x, y));
				m_GameBoard.m_CellsData[y][x] = !m_GameBoard.m_CellsData[y][x];
			}
		}
	}
}