#pragma once

#include <vector>
#include <unordered_map>
#include <time.h>

#define CELL_SIZE 20

#define DEFAULT_ROWS_NUM 15
#define DEFAULT_COLS_NUM 15

// Symbols for each state of square
#define UNREVEALED_EMPTY 'E'
#define UNREVEALED_MINE 'M'
#define REVEALED_EMPTY 'B'
#define FLAG_EMPTY 'F'
#define FLAG_MINE 'X'

#define DEFAULT_MINES_NUM 10

#define OUT_OF_BOUNDS(idx, len) !(0 <= idx && idx < len)

std::vector<std::vector<char>> initGameGrid(int numRows, int numCols, int numMines);
void updateGameGrid(std::vector<std::vector<char>>& grid, int row, int col);