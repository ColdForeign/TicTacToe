#pragma once
#include "lowMode.h"										

Selected—ell RandomCoord(char map[][MAP_SIZE], char player)
{
	Selected—ell randCell;

	do
	{
		randCell.X = rand() % 3;
		randCell.Y = rand() % 3;
	} while ((map[randCell.X][randCell.Y] == 'x' || map[randCell.X][randCell.Y] == '0'));

	return randCell;
}
