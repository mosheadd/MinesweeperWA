#pragma once
#include <Windows.h>
#include <vector>

namespace mswa
{
	constexpr auto UNCOVER = 1;
	constexpr auto FLAG = 2;
	constexpr auto EXIT = 3;

	int getNumberInRange(int min_val, int max_val);

	class Map
	{
		std::vector<std::vector<short>> map;
		short height, width;

		enum
		{
			COVERED = 0,
			UNCOVERED = 1,
			FLAGGED = 2,
			MINE = 3,
			FLAGGED_MINE = 4,
		};

	public:
		Map();
		Map(short height, short width);

		~Map();

		void makeRoad(short row, short col);
		void gameloop();

		short getMinesCount(short row, short col);

		bool checkWinCondition();

	};

}
