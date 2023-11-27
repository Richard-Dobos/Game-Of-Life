#include "GameScene.h"

GameScene::GameScene(SDL_Event* e, WindowProperties* windowProperties, SceneManager* sceneManager)
	:Scene(e, windowProperties), m_SceneManager(sceneManager)
{
	loadCellData();
}

void GameScene::update(SDL_Renderer* renderer)
{
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

		for (int i = 5; i < line.size(); i++)
		{
			if (line[i] == ',')
			{
				x = std::stoi(line.substr(5, (i - 5)));
				y = std::stoi(line.substr(i + 1, line.size() - 2));
				break;
			}
		}

		m_GameBoard.aliveCells.emplace_back(std::make_tuple(x, y));
	}

	m_FileManager->clearLoadBuffer();
}