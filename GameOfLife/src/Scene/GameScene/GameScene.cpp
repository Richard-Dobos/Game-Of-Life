#include "GameScene.h"

GameScene::GameScene(SDL_Event* e, WindowProperties* windowProperties, SceneManager* sceneManager)
	:Scene(e, windowProperties), m_Camera(&m_GameBoard, m_WindowProperties), m_SceneManager(sceneManager)
{
	loadCellData();
	setBoardStatus();
}

void GameScene::setBoardStatus()
{
	for (const auto& cell : m_GameBoard.m_AliveCells)
	{
		const auto& [x, y] = cell.second;

		m_GameBoard.m_CellsData[y][x] = true;
	}
}

void GameScene::loadCellData()
{
	m_FileManager->loadFromFileToLoadBuffer();
	std::vector<std::string> loadBuffer = m_FileManager->loadDataFromCategory("CellData");
	std::string category;

	for (int i = 1; i < loadBuffer.size(); i++)
	{
		std::string line = loadBuffer[i];
		int x, y;

		for (int n = 5; n < line.size(); n++)
		{
			if (line[n] == ',')
			{
				x = std::stoi(line.substr(5, (n - 5)));
				y = std::stoi(line.substr(n + 1, line.size() - n - 2));
				break;
			}
		}

		m_GameBoard.m_AliveCells[x + y + (y * m_GameBoard.m_GameBoardWidth)] = (std::make_tuple(x, y));
	}

	m_FileManager->clearLoadBuffer();
}

void GameScene::update(SDL_Renderer* renderer)
{
	m_Camera.render(renderer);
	m_Camera.updateCameraPosition(m_Event);
	m_GameBoard.update(60);
}