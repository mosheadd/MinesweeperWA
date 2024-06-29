#include "mswa.h"

int mswa::getNumberInRange(int min_val, int max_val)
{
	return min_val + rand() % max_val;
}

mswa::Map::Map()
{
	height = 10;
	width = 10;
}

mswa::Map::Map(short height, short width)
{
	this->height = height;
	this->width = width;
}

mswa::Map::~Map()
{
}

void mswa::Map::makeRoad(short row, short col)
{

	if (row < 0 || row > 9 || col < 0 || col > 9 || map[row][col] == UNCOVERED || map[row][col] == MINE || map[row][col] == FLAGGED_MINE) return;

	int cell_mines_count = getMinesCount(row, col);

	map[row][col] = UNCOVERED;

	if (cell_mines_count > 0) return;

	makeRoad(row - 1, col - 1);
	makeRoad(row - 1, col);
	makeRoad(row - 1, col + 1);
	makeRoad(row, col - 1);
	makeRoad(row, col + 1);
	makeRoad(row + 1, col - 1);
	makeRoad(row + 1, col);
	makeRoad(row + 1, col + 1);

}

short mswa::Map::getMinesCount(short row, short col)
{

	int mines_count = 0;

	if (row >= 1 && row <= 8 && col >= 1 && col <= 8)
	{
		for (int t = row - 1; t < row + 2; t++)
			for (int k = col - 1; k < col + 2; k++)
				mines_count += map[t][k] == MINE || map[t][k] == FLAGGED_MINE;
	}
	else if (col >= 1 && col <= 8)
	{

		if (row == 0)
		{
			for (int t = 0; t < 2; t++)
				for (int k = col - 1; k < col + 2; k++)
					mines_count += map[t][k] == MINE || map[t][k] == FLAGGED_MINE;
		}
		else
		{
			for (int t = 8; t < 10; t++)
				for (int k = col - 1; k < col + 2; k++)
					mines_count += map[t][k] == MINE || map[t][k] == FLAGGED_MINE;
		}
	}
	else if (row >= 1 && row <= 8)
	{
		if (col == 0)
		{
			for (int t = row - 1; t < row + 2; t++)
				for (int k = 0; k < 2; k++)
					mines_count += map[t][k] == MINE || map[t][k] == FLAGGED_MINE;
		}
		else
		{
			for (int t = row - 1; t < row + 2; t++)
				for (int k = 8; k < 10; k++)
					mines_count += map[t][k] == MINE || map[t][k] == FLAGGED_MINE;
		}
	}
	else
	{
		short coeff1 = (row == 0) - (row == 9);
		short coeff2 = (col == 0) - (col == 9);
		mines_count += map[row + coeff1][col + coeff2] == MINE + map[row][col + coeff2] == MINE + map[row + coeff1][col] == MINE;
		mines_count += map[row + coeff1][col + coeff2] == FLAGGED_MINE + map[row][col + coeff2] == FLAGGED_MINE + map[row + coeff1][col] == FLAGGED_MINE;
	}

	return mines_count;

}

void mswa::Map::gameloop()
{
}

bool mswa::Map::checkWinCondition()
{
	for (auto i : map)
	{
		for (auto j : i)
		{
			if (j == COVERED || j == FLAGGED)
				return false;
		}
	}

	return true;
}


