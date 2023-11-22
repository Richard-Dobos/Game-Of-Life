#include "GameBoard.h"

GameBoard::GameBoard(int height, int width)
	:m_GameBoardHeight(height), m_GameBoardWidth(width)
{
	for (int y = 0; y < m_GameBoardHeight; y++)
	{
		std::vector<bool> temp;

		for (int x = 0; x < m_GameBoardWidth; x++)
			temp.emplace_back(false);

		m_CellsData.emplace_back(temp);
	}
}

void GameBoard::update()
{
	checkAliveCellsStatus();
	checkDeadCellsStatus();
}

bool GameBoard::checkCellStatus(int xPos, int yPos, bool status)
{
	int neighbors = 0;

	std::vector<int> checkSum = checkBoundaries(xPos, yPos);

	for (int y = checkSum[0]; y <= checkSum[1]; y++)
	{
		for (int x = checkSum[2]; x <= checkSum[3]; x++)
		{
			if (y == 0 && x == 0)
			{
				continue;
			}

			if (m_CellsData[yPos + y][xPos + x] == true)
			{
				neighbors += 1;
			}
		}
	}

	if (status)
		return neighbors < 2 || neighbors > 3 ? false : true;

	return neighbors == 3 ? true : false;
}

void GameBoard::checkDeadCellsStatus()
{
	std::vector<std::vector<int>> deadCellsCoords = checkAdjacentCellsForStatus();

	for (std::vector<int> deadCellCoords : deadCellsCoords)
	{
		if (checkCellStatus(deadCellCoords[0], deadCellCoords[1], false))
		{
			m_CellsData[deadCellCoords[1]][deadCellCoords[0]] = checkCellStatus(deadCellCoords[0], deadCellCoords[1], false);
			aliveCells.emplace_back(std::make_tuple(deadCellCoords[0], deadCellCoords[1]));
		}
	}
}

void GameBoard::checkAliveCellsStatus()
{
	for (int i = 0; i < aliveCells.size(); i++)
	{
		const auto& [x, y] = aliveCells[i];

		if (!checkCellStatus(x, y, true))
		{
			m_CellsData[x][y] = false;
			aliveCells.erase(aliveCells.begin() + i);

			i += -1;
		}
	}
}

std::vector<std::vector<int>> GameBoard::checkAdjacentCellsForStatus()
{
	std::vector<std::vector<int>> deadCellsCoords;

	for (int y = 0; y < m_CellsData.size(); y++)
	{
		for (int x = 0; x < m_CellsData[y].size(); x++)
		{
			if (m_CellsData[y][x] == false)
			{
				std::vector<int> coords = { x, y };

				deadCellsCoords.emplace_back(coords);
			}
		}
	}

	return deadCellsCoords;
}

std::vector<int> GameBoard::checkBoundaries(int x, int y) const
{
	std::vector<int> checkSum;

	if (y == 0)
	{
		checkSum.emplace_back(0);
		checkSum.emplace_back(1);
	}

	else if (y == m_GameBoardHeight - 1)
	{
		checkSum.emplace_back(-1);
		checkSum.emplace_back(0);
	}

	else
	{
		checkSum.emplace_back(-1);
		checkSum.emplace_back(1);
	}

	if (x == 0)
	{
		checkSum.emplace_back(0);
		checkSum.emplace_back(1);
	}

	else if (x == m_GameBoardWidth - 1)
	{
		checkSum.emplace_back(-1);
		checkSum.emplace_back(0);
	}

	else
	{
		checkSum.emplace_back(-1);
		checkSum.emplace_back(1);
	}

	return checkSum;
}