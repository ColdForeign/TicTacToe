#include "hardMode.h" 

Selected�ell Hard(char map[][MAP_SIZE], char player)
{
	/*
		������� ��� ������� ������ ���,
	*/
	char anotherPlayer;
	Selected�ell newCell;

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
			return { 1, 1 };	// ���� 2 ������� �������� ������ �� ����� �����, �� ������� ������� � ��������
		}
		else if (map[1][0] == anotherPlayer || map[0][1] == anotherPlayer)
		{
			return { 0, 0 };	// ���� ������ ��������� ������ � ������ ������������ ��� �������������� ���, ������� ������
		}						// � ���� ������ ���� 
		else if (map[1][2] == anotherPlayer)
		{
			return { 0, 2 };	// ���� � 3 ������������ ��� �� ������� �� �� ������� ��� ���
		}
		else if (map[1][1] == anotherPlayer || map[2][1] == anotherPlayer)
		{
			return { 2 , 0 };	// ���� �� ������ ��� �� ��� �� ������� � ���� ����� ����
		}
	}
	// ���� ������� ����� ��� �� ���������� �� ��������� ������� ��� ���������� ������
	newCell = Medium(map, anotherPlayer);

	return newCell;
}