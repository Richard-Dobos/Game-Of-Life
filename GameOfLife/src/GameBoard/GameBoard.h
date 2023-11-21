#pragma once

/*
	1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
	2. Any live cell with two or three live neighbours lives on to the next generation.
	3. Any live cell with more than three live neighbours dies, as if by overpopulation.
	4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/

#include <vector>
#include <iostream>
#include <SDL.h>

#include "../Cell/Cell.h"

class GameBoard
{
public:
	GameBoard(int gameBoardHeight = 1024, int gameBoardWidth = 1024);


	void printBoard() const;
	void printAliveCellsData() const;
	void update();
	
	int getAliveCellVecSize() const;

	Cell* getAliveCell(int index);

private:
	bool checkCellStatus(int xPos, int yPos, bool status);

	void checkAliveCellsStatus();
	void checkDeadCellsStatus();

	std::vector<std::vector<int>> checkAdjacentCellsForStatus();
	std::vector<int> checkBoundaries(int x, int y) const;

public:
	int scale = 10;
	int m_GameBoardHeight, m_GameBoardWidth;
	
	std::vector<Cell> aliveCells;
	std::vector<std::vector<Cell>> cells;

private:
	std::vector<std::vector<bool>> cellsData;

	int m_Rows, m_Columns;
};