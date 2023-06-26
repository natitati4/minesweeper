#include "minesweeper.hpp"
#include <iostream>

std::vector<std::vector<char>> initGameGrid(int numRows, int numCols, int numMines)
{
	std::vector<std::vector<char>> grid(numRows, std::vector<char>(numCols, UNREVEALED_EMPTY));

	// Seed rand
	srand(time(NULL));

	// Fill with mines
	for (int i = 0; i < numMines; ++i)
	{
		int row = rand() % numRows;
		int col = rand() % numCols;

		while (grid[row][col] != UNREVEALED_EMPTY)
		{
			row = rand() % numRows;
			col = rand() % numCols;
		}

		grid[row][col] = UNREVEALED_MINE;
	}

	return grid;
}

void updateGameGrid(std::vector<std::vector<char>>& grid, int row, int col)
{
	// Count mines around. First one is guaranteed to be an unrevealed square (empty or with mine)
	int mines = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int newRow = row + i;
			int newCol = col + j;

			// If self or out of bounds
			if ((i == 0 && j == 0) || !(0 <= newRow && newRow < grid.size()) || !(0 <= newCol && newCol < grid[0].size()))
				continue;

			mines += grid[newRow][newCol] == UNREVEALED_MINE; // Will add 1 if mine
		}
	}

	// If there are mines around, turn to number of mines
	if (0 < mines)
		grid[row][col] = mines;

	// If no mines around, mark as revealed empty and recursively check adjacent squares
	else
	{
		grid[row][col] = REVEALED_EMPTY;

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				int newRow = row + i;
				int newCol = col + j;

				// If self, out of bounds or not an unrevealed empty square
				if ((i == 0 && j == 0) || OUT_OF_BOUNDS(newRow, grid.size()) || OUT_OF_BOUNDS(newCol, grid[0].size()) || grid[newRow][newCol] != UNREVEALED_EMPTY)
					continue;

				updateGameGrid(grid, newRow, newCol);
			}
		}
	}
}