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

struct SelectedСell
{
	size_t X = 0;
	size_t Y = 0;
};
// Створює динаміний массив рішітки ігрого поля.
wchar_t** CreateAndFillGameGrid();

// Показує ігрове поле
void ShowGameGrid(const wchar_t* const* gameGrid, const char map[][MAP_SIZE], size_t gridColor);

// Виводить курсор та видаляє його зі старої позиції.
void FillSelectedCell(SelectedСell chosenCell, SelectedСell earlyCell, char map[][MAP_SIZE], char player);

// Видаляє рішітку з памяті
void DeleteGameGrid(wchar_t** gameGrid);

// Вставновлює координати
COORD SetCord(SelectedСell cell);

// Вставновлює координати
void SetCord(COORD CoordCell, size_t coordY);

// Керування
SelectedСell* HighlightSelCell(SelectedСell* chosenCell, char map[][MAP_SIZE], char player, int cellColor);

// Шукає пусту клітинку, щоб поставити туди курсор
void FindEmptyCell(SelectedСell* chosenCell, const char map[][MAP_SIZE]);

// Ховає курсор 
void HideConsoleCursor();

// Показує хто ходить
void ShowWhoWalks(char player);

// Встановлює координати для попередньої функції.
void SetInfoCoord(COORD coordWalkInfo, size_t coordY);
