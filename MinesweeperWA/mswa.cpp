#include "mswa.h"

int mswa::getNumberInRange(int min_val, int max_val)
{
	return min_val + (rand() % (max_val - min_val + 1));
}

mswa::Map::Map()
{
	height = 10;
	width = 10;
	init();
}

mswa::Map::Map(short height, short width)
{
	this->height = height;
	this->width = width;
	init();
}

mswa::Map::~Map()
{
}

void mswa::Map::makeRoad(short row, short col)
{

	if (row < 0 || row >= height || col < 0 || col >= width || map[row][col] == UNCOVERED || map[row][col] == MINE || map[row][col] == FLAGGED_MINE) return;

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

	if (row >= 1 && row <= height - 2 && col >= 1 && col <= width - 2)
	{
		for (int t = row - 1; t < row + 2; t++)
			for (int k = col - 1; k < col + 2; k++)
				mines_count += map[t][k] == MINE || map[t][k] == FLAGGED_MINE;
	}
	else if (col >= 1 && col <= width - 2)
	{

		if (row == 0)
		{
			for (int t = 0; t < 2; t++)
				for (int k = col - 1; k < col + 2; k++)
					mines_count += map[t][k] == MINE || map[t][k] == FLAGGED_MINE;
		}
		else
		{
			for (int t = height - 2; t < height; t++)
				for (int k = col - 1; k < col + 2; k++)
					mines_count += map[t][k] == MINE || map[t][k] == FLAGGED_MINE;
		}
	}
	else if (row >= 1 && row <= width - 2)
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
				for (int k = width - 2; k < width; k++)
					mines_count += map[t][k] == MINE || map[t][k] == FLAGGED_MINE;
		}
	}
	else
	{
		short coeff1 = (row == 0) - (row == (height - 1));
		short coeff2 = (col == 0) - (col == (width - 1));
		mines_count += (map[row + coeff1][col + coeff2] == MINE) + (map[row][col + coeff2] == MINE) + (map[row + coeff1][col] == MINE);
		mines_count += (map[row + coeff1][col + coeff2] == FLAGGED_MINE) + (map[row][col + coeff2] == FLAGGED_MINE) + (map[row + coeff1][col] == FLAGGED_MINE);
	}

	return mines_count;

}

short mswa::Map::getCell(short row, short col)
{
	return map[row][col];
}

short mswa::Map::getFlagsCount()
{
	return flags;
}

bool mswa::Map::action(int x, int y, bool toflag)
{

	short row = y / 32;
	short col = x / 32;

	if (row >= height || col >= width) return 1;

	if (toflag)
	{
		switch (map[row][col])
		{
		case COVERED:
			if (flags > 0)
			{
				map[row][col] = FLAGGED;
				flags--;
			}
			break;
		case FLAGGED:
			map[row][col] = COVERED;
			flags++;
			break;
		case MINE:
			if (flags > 0)
			{
				map[row][col] = FLAGGED_MINE;
				flags--;
			}
			break;
		case FLAGGED_MINE:
			map[row][col] = MINE;
			flags++;
			break;
		default:
			break;
		}
	}
	else
	{
		if (map[row][col] == MINE || map[row][col] == FLAGGED_MINE)
		{
			return 0;
		}
		else
		{
			makeRoad(row, col);
			return 1;
		}
	}

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

void mswa::Map::init()
{
	for (short i = 0; i < height; i++)
	{
		map.push_back({});
		for (short j = 0; j < width; j++)
			map[i].push_back(COVERED);
	}

}

void mswa::Map::reinit()
{
	for (short i = 0; i < height; i++)
	{
		for (short j = 0; j < width; j++)
			map[i][j] = COVERED;
	}

}

void mswa::Map::initMines(int x, int y)
{

	short row = y / 32;
	short col = x / 32;

	short totalMinesOnMap = getNumberInRange(3 * height * width / 20, 3 * height * width / 10);
	short mineRow = row;
	short mineCol = col;

	for (short i = 0; i < totalMinesOnMap; i++)
	{
		while (mineRow == row && mineCol == col || map[mineRow][mineCol] == MINE)
		{	
			mineRow = getNumberInRange(0, height - 1);
			mineCol = getNumberInRange(0, width - 1);
		}
		map[mineRow][mineCol] = MINE;
	}

	flags = totalMinesOnMap;

}

mswa::Map::Size mswa::Map::getSize()
{
	Size size = { height, width };
	return size;
}
