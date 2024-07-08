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
		short height, width, flags;
		
		void init();

		struct Size {
			short height, width;

			Size(short height, short width) : height(height), width(width){}
		};

	public:

		enum
		{
			COVERED = 0,
			UNCOVERED = 1,
			FLAGGED = 2,
			MINE = 3,
			FLAGGED_MINE = 4,
		};

		Map();
		Map(short height, short width);

		~Map();

		void makeRoad(short row, short col);
		void initMines(int x, int y);
		void reinit();

		short getMinesCount(short row, short col);
		short getCell(short row, short col);
		short getFlagsCount();

		bool action(int x, int y, bool toflag = false);
		bool checkWinCondition();

		Size getSize();

	};

}
