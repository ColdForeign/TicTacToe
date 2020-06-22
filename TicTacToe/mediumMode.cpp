#include "mediumMode.h"

bool SearchWin(char map[][MAP_SIZE], Selected�ell& newCell, char player, char anotherPlayer)
{
	/*
		���� ��� � ������� ���� �������.
	*/
	char tempMap[MAP_SIZE][MAP_SIZE];
	char movesMap[MAP_SIZE][MAP_SIZE];


	size_t moves = MAP_SIZE * MAP_SIZE;
	size_t movesLeft = 0;
	for (size_t x = 0; x < MAP_SIZE; x++)
		for (size_t y = 0; y < MAP_SIZE; y++) {
			movesMap[x][y] = map[x][y];
			if (map[x][y] == 'x' || map[x][y] == '0')
				moves--;
		}

	do
	{
		for (size_t x = 0; x < MAP_SIZE; x++)
			for (size_t y = 0; y < MAP_SIZE; y++)
				tempMap[x][y] = map[x][y];

		newCell = RandomCoord(movesMap, anotherPlayer);
		tempMap[newCell.X][newCell.Y] = player;
		movesMap[newCell.X][newCell.Y] = player;

		if (GameBoard�heck(tempMap, player) == WIN)
		{
			return true;
		}

		movesLeft++;
	} while (movesLeft < moves);

	return false;
}

Selected�ell Medium(char map[][MAP_SIZE], char player)
{
	/*
		������� ��������� ���� ������� ������.
	*/
	char anotherPlayer;
	Selected�ell newCell;

	if (player == 'x')
		anotherPlayer = '0';
	else
		anotherPlayer = 'x';

	if (SearchWin(map, newCell, player, anotherPlayer))
		return newCell;
	else if (SearchWin(map, newCell, anotherPlayer, player))
		return newCell;
	else
		newCell = RandomCoord(map, player);
	return newCell;
}