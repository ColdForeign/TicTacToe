#include "hardMode.h" 

SelectedСell Hard(char map[][MAP_SIZE], char player)
{
	/*
		Функція для тяжкого режиму гри,
	*/
	char anotherPlayer;
	SelectedСell newCell;

	if (player == 'x')
		anotherPlayer = '0';
	else
		anotherPlayer = 'x';

	size_t moves = 0;

	for (size_t x = 0; x < MAP_SIZE; x++)
		for (size_t y = 0; y < MAP_SIZE; y++)
			if (map[x][y] == 'x' || map[x][y] == '0')
				moves++;

	if (moves == 0)
	{
		return { 0, 2 };
	}
	else if (moves == 1)
	{
		if (map[0][0] == anotherPlayer || map[2][2] == anotherPlayer || map[0][2] == anotherPlayer || map[2][0] == anotherPlayer)
		{
			return { 1, 1 };	// Якщо 2 гравець поставив символ по краям карти, то функція ставить в середину
		}
		else if (map[1][0] == anotherPlayer || map[0][1] == anotherPlayer)
		{
			return { 0, 0 };	// Якщо людина поставила символ в перший вертикальний або горизонтальний ряд, ставить символ
		}						// в лівий верхній край 
		else if (map[1][2] == anotherPlayer)
		{
			return { 0, 2 };	// Якщо в 3 вертикальний ряд по середині то та ставить над ним
		}
		else if (map[1][1] == anotherPlayer || map[2][1] == anotherPlayer)
		{
			return { 2 , 0 };	// Якщо по центру або під ним то ставить в лівий нижній край
		}
	}
	// Якщо пепердні умови вже не виконуются то спрацьовує функція для середнього режиму
	newCell = Medium(map, anotherPlayer);

	return newCell;
}