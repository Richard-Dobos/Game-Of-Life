#pragma once

/*
	1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
	2. Any live cell with two or three live neighbours lives on to the next generation.
	3. Any live cell with more than three live neighbours dies, as if by overpopulation.
	4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/

#include <map>
#include <SDL.h>
#include <iostream>

#include "../Timer/Timer.h"
#include "../FileManager/FileManager.h"

class GameBoard
{
public:
	GameBoard(int gameBoardHeight = 1024, int gameBoardWidth = 1024);

	void update(int tickRate);
	void resetBoard();

public:
	int m_GameBoardHeight, m_GameBoardWidth;
	int scale = 2;
	bool m_Changed = true;

	std::vector<std::vector<bool>> m_CellsData;
	std::map<int, std::tuple<int, int>> m_AliveCells;

private:
	void checkAliveCellsStatus();
	void checkDeadCellsStatus();
	void getNeighboringDeadCells();
	bool checkCellStatus(int xPos, int yPos, bool status);
	
	std::vector<int> checkBoundaries(int x, int y) const;
	
private:
	int ticks = 1;

	std::vector<std::tuple<int, int>> m_DeadNeighboringCells;

	size_t aliveCellsPrevSize = m_AliveCells.size();
};