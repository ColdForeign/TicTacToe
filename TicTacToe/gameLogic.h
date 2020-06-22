#pragma once
#define MAP_SIZE 3
#define WIN 0
#define NOTHING 1
#define STANDOFF 2

bool HorizontalCheck(char map[][MAP_SIZE], char player);	// �������� ������� ���� �� ����������
bool VerticalCheck(char map[][MAP_SIZE], char player);		// �������� ������� ���� �� ��������
bool DiagonalCheck(char map[][MAP_SIZE], char player);		// �������� ������� ���� �� ���������
int GameBoard�heck(char map[][MAP_SIZE], char player);		// ������ ���������� 3-�� ��������� �������.