#include "mediumMode.h"

bool SearchWin(char map[][MAP_SIZE], SelectedСell& newCell, char player, char anotherPlayer)
{
	/*
		Шукає хто з гравців може виграти.
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

		if (GameBoardСheck(tempMap, player) == WIN)
		{
			return true;
		}

		movesLeft++;
	} while (movesLeft < moves);

	return false;
}

SelectedСell Medium(char map[][MAP_SIZE], char player)
{
	/*
		Функція прораховує куди ставити символ.
	*/
	char anotherPlayer;
	SelectedСell newCell;

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