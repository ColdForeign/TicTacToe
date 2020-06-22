#pragma once
#include "gameBoard.h"

void HideConsoleCursor() {
	/*
		Ховає консольний курсор
	*/
	GET_HANDLE(hConsole);
	CONSOLE_CURSOR_INFO consoleCursor;
	GetConsoleCursorInfo(hConsole, &consoleCursor);
	consoleCursor.bVisible = false;
	SetConsoleCursorInfo(hConsole, &consoleCursor);
}

wchar_t** CreateAndFillGameGrid() {
	/*
		Створює динаміний массив рішітки ігрого поля.
	*/
	const wchar_t* FILLED_BLOCK = L"█";
	const wchar_t* SPACE = L" ";

	size_t gridHeight = GAME_GRID_HEIGHT;
	size_t gridWidth = GAME_GRID_WIDHT;
	wchar_t** gameGrid = new wchar_t* [gridHeight];
	for (size_t i = 0; i < gridHeight; i++)
	{
		gameGrid[i] = new wchar_t[gridWidth];
	}

	for (size_t i = 0; i < gridHeight; i++)
	{
		for (size_t j = 0; j < gridWidth; j++)
		{
			if (i == 0 || i == gridHeight - 1)
				gameGrid[i][j] = *FILLED_BLOCK;
			else if (j == 0 || j == 1 || j == gridWidth - 1 || j == gridWidth - 2)
				gameGrid[i][j] = *FILLED_BLOCK;
			else if (i == 6 || i == 12 || i == 25)
				gameGrid[i][j] = *FILLED_BLOCK;
			else if (j == 13 || j == 14 || j == 26 || j == 27)
				gameGrid[i][j] = *FILLED_BLOCK;
			else gameGrid[i][j] = *SPACE;
		}
	}
	return gameGrid;
}

void DeleteGameGrid(wchar_t** gameGrid) {
	/*
		Видаляє рішітку з памяті
	*/
	size_t gridHeight = GAME_GRID_HEIGHT;
	for (size_t i = 0; i < gridHeight; i++)
		delete[] gameGrid[i];
	delete[] gameGrid;
}

void ShowGameGrid(const wchar_t* const* gameGrid, const char map[][MAP_SIZE], size_t gridColor) {
	/*
		Показує ігрове поле
	*/
	size_t gridHeight = GAME_GRID_HEIGHT;
	size_t gridWidth = GAME_GRID_WIDHT;

	GET_HANDLE(hConsole);
	SelectedСell imageCoord;
	COORD gridCoord;
	OUTPUT_MODE_UNICODE;
	gridCoord.X = 0;
	gridCoord.Y = 0;
	system("cls");
	SetConsoleCursorPosition(hConsole, gridCoord);
	for (size_t i = 0; i < gridHeight; i++)
	{
		for (size_t j = 0; j < gridWidth; j++)
		{
			SetConsoleTextAttribute(hConsole, (WORD)gridColor);
			wcout << gameGrid[i][j];
		}
		wcout << endl;
	}

	OUTPUT_MODE_UNICODE;
	for (size_t x = 0; x < 3; x++)
	{

		for (size_t y = 0; y < 3; y++)
		{
			imageCoord.X = x;
			imageCoord.Y = y;
			gridCoord = SetCord(imageCoord);

			for (size_t i = 0; i < PICTURE_HEIGHT; i++)
			{
				SetCord(gridCoord, short(i));
				SetConsoleTextAttribute(hConsole, (map[x][y] == 'x') ? LightBlue : LightPurple);
				for (size_t j = 0; j < PICTURE_WIDTH; j++)
				{
					if (map[x][y] == 'x')
						wcout << CROSS[i][j];
					else if (map[x][y] == '0')
						wcout << TOE[i][j];
					else
						continue;
				}
				wcout << endl;
			}
		}
	}
	system("color 0");
	OUTPUT_MODE_TEXT;
}
void SetInfoCoord(COORD coordWalkInfo, size_t coordY) {
	/*
		Функція для встановлення позиції виводу інвормації
	*/
	GET_HANDLE(hConsole);
	coordY = short(coordY);
	coordWalkInfo.X += 0;
	coordWalkInfo.Y += coordY;
	SetConsoleCursorPosition(hConsole, coordWalkInfo);
}

COORD SetCord(SelectedСell cell) {
	/*
		Функція переводить кординати карти 3на3,
		якіми ми отримали переключаючи конпками,
		в кординати динаміного масиву решітки і
		ставить на їх місце курсор.
	*/
	GET_HANDLE(hConsole);
	COORD CoordCell;
	CoordCell.X = 0;
	CoordCell.Y = 0;

	if (cell.X == 0)
		CoordCell.X = 2;
	if (cell.X == 1)
		CoordCell.X = 4 + PICTURE_WIDTH;
	if (cell.X == 2)
		CoordCell.X = 6 + PICTURE_WIDTH * 2;

	if (cell.Y == 0)
		CoordCell.Y = 1;
	if (cell.Y == 1)
		CoordCell.Y = 2 + PICTURE_HEIGHT;
	if (cell.Y == 2)
		CoordCell.Y = 3 + PICTURE_HEIGHT * 2;

	SetConsoleCursorPosition(hConsole, CoordCell);
	return CoordCell;
}

void SetCord(COORD CoordCell, size_t coordY) {
	/*
		Функція ставить переключає кординату Y
		на новий рядок(для виводу массивів)
	*/
	coordY = short(coordY);
	GET_HANDLE(hConsole);
	CoordCell.X += 0;
	CoordCell.Y += coordY;
	SetConsoleCursorPosition(hConsole, CoordCell);
}

void FillSelectedCell(SelectedСell chosenCell, SelectedСell earlyCell, char map[][MAP_SIZE], char player) {
	/*
		Виводить курсор та видаляє його зі старої позиції.
	*/
	GET_HANDLE(hConsole);

	HideConsoleCursor();

	OUTPUT_MODE_UNICODE;
	COORD coordEarly = SetCord(earlyCell);

	for (size_t i = 0; i < PICTURE_HEIGHT; i++)
	{
		SetCord(coordEarly, i);
		if (map[coordEarly.X][coordEarly.Y] == 'x')
			SetConsoleTextAttribute(hConsole, LightBlue);
		else if (map[coordEarly.X][coordEarly.Y] == '0')
			SetConsoleTextAttribute(hConsole, LightPurple);

		for (size_t j = 0; j < PICTURE_WIDTH; j++)
		{
			if (map[earlyCell.X][earlyCell.Y] == 'x')
				wcout << CROSS[i][j];
			if (map[earlyCell.X][earlyCell.Y] == '0')
				wcout << TOE[i][j];
			if (map[earlyCell.X][earlyCell.Y] == ' ')
				wcout << ' ';
		}
		wcout << endl;
	}
	OUTPUT_MODE_TEXT;


	OUTPUT_MODE_UNICODE;
	COORD coordChosen = SetCord(chosenCell);
	size_t x = chosenCell.X;
	size_t y = chosenCell.Y;
	for (size_t i = 0; i < PICTURE_HEIGHT; i++)
	{
		SetCord(coordChosen, i);
		SetConsoleTextAttribute(hConsole, LightGreen);
		for (size_t j = 0; j < PICTURE_WIDTH; j++)
		{
			if (map[x][y] != ' ') {
				if (CURSOR[i][j] != ' ')
				{
					SetConsoleTextAttribute(hConsole, Red);
					wcout << CURSOR[i][j];
				}
				else if (IMAGE_NAME(map[x][y])[i][j] != ' ')
				{
					SetConsoleTextAttribute(hConsole, ((map[x][y] == 'x') ? LightBlue : LightPurple));
					wcout << IMAGE_NAME(map[x][y])[i][j];
				}
				else
					if ((CURSOR[i][j] == ' ') && (IMAGE_NAME(map[x][y])[i][j] == ' '))
						wcout << ' ';
			}
			else
				wcout << CURSOR[i][j];

		}
		wcout << endl;
	}
	OUTPUT_MODE_TEXT;
}

void FindEmptyCell(SelectedСell* chosenCell, const char map[][MAP_SIZE])
{
	/*
		Шукає порожню клітинку, щоб поставити туди курсор.
	*/
	bool filled = false;
	for (size_t i = 0; i < MAP_SIZE; i++)
	{
		if (filled)
			break;
		for (size_t j = 0; j < MAP_SIZE; j++)
		{
			if (map[i][j] == ' ' && map[i][j] != 'x' && map[i][j] != '0')
			{
				chosenCell->X = i;
				chosenCell->Y = j;
				filled = true;
				break;
			}
		}
	}
}

void ShowWhoWalks(char player) {
	/*
		Виводить символ того, хто зарез ходить.
	*/
	GET_HANDLE(hConsole);
	OUTPUT_MODE_TEXT;
	COORD coordWalkInfo;
	COORD sizeWindow = GetLargestConsoleWindowSize(hConsole);
	char message[] = "Now walking: ";
	coordWalkInfo.X = GAME_GRID_WIDHT + (sizeWindow.X - GAME_GRID_WIDHT) / 2 - strlen(message) / 2;
	coordWalkInfo.Y = 5;
	SetConsoleCursorPosition(hConsole, coordWalkInfo);
	cout << message;
	coordWalkInfo.Y = 7;

	for (size_t i = 0; i < PICTURE_HEIGHT; i++)
	{
		SetCord(coordWalkInfo, i);
		for (size_t j = 0; j < PICTURE_WIDTH; j++)
		{
			cout << " ";
		}
		cout << endl;
	}
	coordWalkInfo.Y = 7;

	OUTPUT_MODE_UNICODE;
	for (size_t i = 0; i < PICTURE_HEIGHT; i++)
	{
		SetCord(coordWalkInfo, i);
		SetConsoleTextAttribute(hConsole, (player == 'x') ? LightBlue : LightPurple);
		for (size_t j = 0; j < PICTURE_WIDTH; j++)
		{
			wcout << ((player == 'x') ? CROSS[i][j] : TOE[i][j]);
		}
		wcout << endl;
	}
	OUTPUT_MODE_TEXT;
}

SelectedСell* HighlightSelCell(SelectedСell* chosenCell, char map[][MAP_SIZE], char player, int cellColor) {
	/*
		Функція яка дає можливість керувати клавіатурою,
		інформіцію про поточну клітинку записує в структуру.
	*/
	GET_HANDLE(hConsole);

	SelectedСell earlyCell;

	FindEmptyCell(chosenCell, map);
	FindEmptyCell(&earlyCell, map);
	ShowWhoWalks(player);
	FillSelectedCell(*chosenCell, earlyCell, map, cellColor);
	bool notChoice = false;
	int buttonID = _getch();

	if (buttonID == BUTTON_ENTER)
		return chosenCell;
	do
	{
		buttonID = _getch();
		if (buttonID == ARROW_DOWN || buttonID == 's' || buttonID == 'S')		//down
		{
			earlyCell.Y = chosenCell->Y;
			earlyCell.X = chosenCell->X;
			if (chosenCell->Y == 2)
				chosenCell->Y = 0;
			else
				chosenCell->Y += 1;

			FillSelectedCell(*chosenCell, earlyCell, map, cellColor);
		}

		if (buttonID == ARROW_UP || buttonID == 'w' || buttonID == 'W')		//up
		{
			earlyCell.Y = chosenCell->Y;
			earlyCell.X = chosenCell->X;
			if (chosenCell->Y == 0)
				chosenCell->Y = 2;
			else
				chosenCell->Y -= 1;

			FillSelectedCell(*chosenCell, earlyCell, map, cellColor);
		}

		if (buttonID == ARROW_LEFT || buttonID == 'a' || buttonID == 'A')		//left
		{
			earlyCell.Y = chosenCell->Y;
			earlyCell.X = chosenCell->X;
			if (chosenCell->X == 0)
				chosenCell->X = 2;
			else
				chosenCell->X -= 1;

			FillSelectedCell(*chosenCell, earlyCell, map, cellColor);
		}

		if (buttonID == ARROW_RIGHT || buttonID == 'd' || buttonID == 'D')		//right
		{
			earlyCell.Y = chosenCell->Y;
			earlyCell.X = chosenCell->X;
			if (chosenCell->X == 2)
				chosenCell->X = 0;
			else
				chosenCell->X += 1;

			FillSelectedCell(*chosenCell, earlyCell, map, cellColor);
		}

		if (buttonID == BUTTON_ENTER || buttonID == BUTTON_SPACE)
		{
			if (map[chosenCell->X][chosenCell->Y] == 'x' || map[chosenCell->X][chosenCell->Y] == '0')
			{
				continue;	// Якщо курсор на заповненій клітинці, то пропустити  
			}
			notChoice = true;
			return chosenCell;
		}

	} while (!notChoice);
	return nullptr;
}
