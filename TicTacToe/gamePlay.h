#pragma once
#define MAP_SIZE 3

// ������ � ����� ������ ������
void AddToGameMap(Selected�ell* chosenCell, char map[][MAP_SIZE], char symbol);

// �������� ������
char PlayerSwitch(char player);

// ������� ������� ������� � ���� ���� �������(��� ��� � ز)
Selected�ell OtherPlayerWalk(char map[][MAP_SIZE], int difficulty, char player);