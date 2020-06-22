#pragma once
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <conio.h>
#include "pictures.cpp"
#include "consoleColors.cpp"
using namespace std;

#define GET_HANDLE(name) HANDLE (name) = GetStdHandle(STD_OUTPUT_HANDLE)
#define IMAGE_NAME(player) (player == 'x'? CROSS: TOE)
#define OUTPUT_MODE_UNICODE _setmode(_fileno(stdout), _O_U8TEXT)
#define OUTPUT_MODE_TEXT _setmode(_fileno(stdout), _O_TEXT)

#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define BUTTON_ENTER 13
#define BUTTON_ESCAPE 27
#define BUTTON_SPACE 32
#define GAME_GRID_HEIGHT 19
#define GAME_GRID_WIDHT 41
#define PICTURE_HEIGHT 5
#define PICTURE_WIDTH 11
#define MAP_SIZE 3

struct Selected�ell
{
	size_t X = 0;
	size_t Y = 0;
};
// ������� �������� ������ ������ ������ ����.
wchar_t** CreateAndFillGameGrid();

// ������ ������ ����
void ShowGameGrid(const wchar_t* const* gameGrid, const char map[][MAP_SIZE], size_t gridColor);

// �������� ������ �� ������� ���� � ����� �������.
void FillSelectedCell(Selected�ell chosenCell, Selected�ell earlyCell, char map[][MAP_SIZE], char player);

// ������� ������ � �����
void DeleteGameGrid(wchar_t** gameGrid);

// ����������� ����������
COORD SetCord(Selected�ell cell);

// ����������� ����������
void SetCord(COORD CoordCell, size_t coordY);

// ���������
Selected�ell* HighlightSelCell(Selected�ell* chosenCell, char map[][MAP_SIZE], char player, int cellColor);

// ���� ����� �������, ��� ��������� ���� ������
void FindEmptyCell(Selected�ell* chosenCell, const char map[][MAP_SIZE]);

// ���� ������ 
void HideConsoleCursor();

// ������ ��� ������
void ShowWhoWalks(char player);

// ���������� ���������� ��� ���������� �������.
void SetInfoCoord(COORD coordWalkInfo, size_t coordY);
