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
	GameBoard(int height = 0, int width = 0, 
		const std::vector<std::vector<bool>>& data =
		{
			{false, false, false, false, false, false, false},
			{true, true, true, false, true, true, false},
			{false, true, true, false, true, true, false},
			{false, false, false, false, false, false, false}
		});

	void printBoard() const;
	void printAliveCellsData() const;

	Cell* getAliveCell(int index);
	int getAliveCellVecSize() const;
	void update();

private:
	bool checkCellStatus(int xPos, int yPos, bool status);
	void checkAliveCellsStatus();
	void checkDeadCellsStatus();
	std::vector<std::vector<int>> checkAdjacentCellsForStatus();

	std::vector<int> checkBoundaries(int x, int y) const;

private:
	int height, width, heightOfCells, widthOfCells;

	std::vector<std::vector<bool>> cellsData;
	std::vector<Cell> aliveCells;
};