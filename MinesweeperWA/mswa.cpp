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
}

void mswa::Map::getMinesCount()
{
}

void mswa::Map::gameloop()
{
}

bool mswa::Map::checkWinCondition()
{
	return false;
}


