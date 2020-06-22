#pragma once
#include "hardMode.h"
using namespace std;

void AddToGameMap(SelectedСell* chosenCell, char map[][MAP_SIZE], char symbol)
{
	/*
		Записує символ в карту
	*/
	size_t x = chosenCell->X;
	size_t y = chosenCell->Y;

	if ((map[x][y] != 'x' && map[x][y] != '0') && map[x][y] == ' ')
	{
		if (x > 2 || x < 0 || y > 2 || y < 0)
			cout << "Error!\nSuch coordinates do not exist.\n";
		else
			map[x][y] = symbol;
	}
}

char PlayerSwitch(char player)
{
	/*
	Змінює гравця
	*/
	if (player == 'x')
		player = '0';
	else if (player == '0')
		player = 'x';
	if (player != 'x' && player != '0')
		return ' ';
	return player;
}

SelectedСell OtherPlayerWalk(char map[][MAP_SIZE], int difficulty, char player)
{
	switch (difficulty)
	{
	case 0:
		return RandomCoord(map, player);
		break;
	case 1:
		return Medium(map, player);
		break;
	case 2:
		return Hard(map, player);
		break;
	}

	return { 0, 0 };
}
