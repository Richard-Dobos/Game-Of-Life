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

void GameBoard::update(int tickRate)
{
	if (ticks % tickRate == 0)
	{
		checkAliveCellsStatus();
		checkDeadCellsStatus();
		ticks = 0;
	}

	ticks += 1;
}

void GameBoard::resetBoard()
{
	for(const auto& cell : m_AliveCells)
	{
		const auto& [x, y] = m_AliveCells.begin()->second;

		m_CellsData[y][x] = false;
	}

	m_AliveCells.clear();
}

void GameBoard::checkAliveCellsStatus()
{
	std::vector<int> indeciesToRemove;

	for(const auto& cell : m_AliveCells)
	{
		const auto& [x, y] = cell.second;

		if (!checkCellStatus(x, y, true))
		{
			m_CellsData[y][x] = false;
			indeciesToRemove.emplace_back(cell.first);
		}
	}

	for (int value : indeciesToRemove)
		m_AliveCells.erase(value);
}

void GameBoard::checkDeadCellsStatus()
{
	getNeighboringDeadCells();

	for (const auto& cell : m_DeadNeighboringCells)
	{
		const auto& [x, y] = cell;

		if (checkCellStatus(x, y, false))
		{
			m_CellsData[y][x] = true;
			m_AliveCells[x + y] = std::make_tuple(x, y);
		}
	}
}

void GameBoard::getNeighboringDeadCells()
{
	for (const auto& cell : m_AliveCells)
	{
		const auto& [xPos, yPos] = cell.second;

		std::vector<int> checkSum = checkBoundaries(xPos, yPos);

		for (int y = checkSum[0]; y <= checkSum[1]; y++)
		{
			for (int x = checkSum[2]; x <= checkSum[3]; x++)
			{
				if (y == 0 && x == 0)
					continue;

				if (m_CellsData[yPos + y][xPos + x] == false)
					m_DeadNeighboringCells.emplace_back(std::make_tuple(xPos + x, yPos + y));
			}
		}
	}
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
				continue;

			if (m_CellsData[yPos + y][xPos + x] == true)
				neighbors += 1;
		}
	}

	if (status)
		return neighbors < 2 || neighbors > 3 ? false : true;

	return neighbors == 3 ? true : false;
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
