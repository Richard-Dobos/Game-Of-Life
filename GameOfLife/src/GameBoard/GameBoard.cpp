#include "GameBoard.h"

GameBoard::GameBoard(int height, int width, const std::vector<std::vector<bool>>& data)
	:height(height), width(width), heightOfCells(data.size()), widthOfCells(data[0].size()), cellsData(data)
{
	for (int y = 0; y < data.size(); y++)
	{
		for (int x = 0; x < data[y].size(); x++)
		{
			if (data[y][x] == true)
			{
				aliveCells.emplace_back(x, y, data[y][x]);
			}
		}
	}
}

Cell* GameBoard::getAliveCell(int index)
{
	return aliveCells.empty() == true ? nullptr : &aliveCells[index];
}

int GameBoard::getAliveCellVecSize() const
{
	return aliveCells.size();
}

void GameBoard::update()
{
	checkAliveCellsStatus();
	checkDeadCellsStatus();
}

void GameBoard::printAliveCellsData() const
{
	for (Cell cellData : aliveCells)
	{
		std::cout << "\nCell Data: |STATE: " << cellData.isAlive() << "| POS: " << cellData.xPos << ", " << cellData.yPos;
	}
}

void GameBoard::printBoard() const
{
	std::cout << '\n';

	for (int i = 0; i < cellsData.size(); i++)
	{
		for (bool dataPoint : cellsData[i])
		{
			if (dataPoint == true)
				std::cout << " O ";
			else
				std::cout << " X ";
		}

		std::cout << '\n';
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
			{
				continue;
			}

			if (cellsData[yPos + y][xPos + x] == true)
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
			cellsData[deadCellCoords[1]][deadCellCoords[0]] = checkCellStatus(deadCellCoords[0], deadCellCoords[1], false);
			aliveCells.emplace_back(deadCellCoords[0], deadCellCoords[1], true);
		}
	}
}

void GameBoard::checkAliveCellsStatus()
{
	for (int i = 0; i < aliveCells.size(); i++)
	{
		if (!checkCellStatus(aliveCells[i].xPos, aliveCells[i].yPos, true))
		{
			cellsData[aliveCells[i].yPos][aliveCells[i].xPos] = false;
			aliveCells.erase(aliveCells.begin() + i);

			i += -1;
		}
	}
}

std::vector<std::vector<int>> GameBoard::checkAdjacentCellsForStatus()
{
	std::vector<std::vector<int>> deadCellsCoords;

	for (int y = 0; y < cellsData.size(); y++)
	{
		for (int x = 0; x < cellsData[y].size(); x++)
		{
			if (cellsData[y][x] == false)
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

	else if (y == heightOfCells - 1)
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

	else if (x == widthOfCells - 1)
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