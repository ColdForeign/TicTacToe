#include "gameLogic.h"

bool HorizontalCheck(char map[][MAP_SIZE], char player)
{
	for (size_t x = 0; x < 3; x++)
	{
		size_t symbolIs = 0;
		for (size_t y = 0; y < 3; y++)
		{
			if (map[x][y] == player)
				symbolIs++;
		}
		if (symbolIs == 3)
			return true;
	}
	return false;
}

bool VerticalCheck(char map[][MAP_SIZE], char player)
{
	for (size_t y = 0; y < 3; y++)
	{
		size_t symbolIs = 0;
		for (size_t x = 0; x < 3; x++)
		{
			if (map[x][y] == player)
				symbolIs++;
		}
		if (symbolIs == 3)
			return true;
	}
	return false;
}

bool DiagonalCheck(char map[][MAP_SIZE], char player)
{
	size_t symbolIs = 0;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if ((i == j) && (map[i][j] == player))
				symbolIs++;
		}
		if (symbolIs == 3)
			return true;
	}

	symbolIs = 0;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if ((i + j == MAP_SIZE - 1) && (map[i][j] == player))
				symbolIs++;
		}
		if (symbolIs == 3)
			return true;
	}
	return false;
}

int GameBoardÑheck(char map[][MAP_SIZE], char player)
{
	int symbolIs = 0;

	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			if (map[i][j] == 'x' || map[i][j] == '0')
				symbolIs++;
		}
	}

	if (HorizontalCheck(map, player))
		return WIN;

	else if (VerticalCheck(map, player))
		return WIN;

	else if (DiagonalCheck(map, player))
		return WIN;

	if (symbolIs == MAP_SIZE * MAP_SIZE)
		return STANDOFF;

	return NOTHING;
}