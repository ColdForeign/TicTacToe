#pragma once
#include "gameBoard.h"
#include "menu.h"

void SetTitleCoord(COORD imageCoord) {
	/*
		Ставить консольний курсор в потрібне місце
	*/
	GET_HANDLE(hConsole);
	COORD titleCoord;
	titleCoord.X = imageCoord.X + PICTURE_WIDTH;
	titleCoord.Y = imageCoord.Y - 2;
	SetConsoleCursorPosition(hConsole, titleCoord);
}

short ShowTitle(COORD imageCoord, int textColor) {
	/*
		Виводить текст з файлу
	*/
	GET_HANDLE(hConsole);

	ifstream infoFile;

	if (imageCoord.X == 0)
	{
		infoFile.open("standoff.txt");
	}
	else
		infoFile.open("whoWin.txt");
	if (!infoFile.is_open())
	{
		cout << "Error!\nFile not found!\n";
		return 0;
	}
	else
	{
		string logoLine2;
		while (!infoFile.eof())
		{
			SetConsoleTextAttribute(hConsole, (WORD)textColor);
			logoLine2 = "";

			getline(infoFile, logoLine2);
			const char* logoLinePointer = logoLine2.c_str();
			if (imageCoord.X == 0)
			{
				SetCursorInTheCenter(logoLinePointer);
			}
			else
				SetTitleCoord(imageCoord);
			cout << logoLine2 << endl;
			imageCoord.Y += 1;
		}
	}
	infoFile.close();
	return imageCoord.Y;
}

void ShowAnimation(COORD imageCoord, COORD sizeWindow, char player)
{	/*
		Показує хто виграв або що ніхто не виграв
	*/
	GET_HANDLE(hConsole);
	OUTPUT_MODE_UNICODE;
	SetConsoleTextAttribute(hConsole, (player == 'x') ? LightBlue : LightPurple);

	const wchar_t GRADIENT[]{ L'█', L'▓', L'▒', L'░' };
	int gradientSize = sizeof(GRADIENT) / sizeof(wchar_t);

	if (sizeWindow.X % 2 != 0)
		sizeWindow.X += 1;

	if (sizeWindow.X % 10 != 0)
		sizeWindow.X += (10 - sizeWindow.X % 10);
	imageCoord.X = (sizeWindow.X / 2) - (4 * sizeWindow.X / 10);
	imageCoord.Y -= 2;
	SetConsoleCursorPosition(hConsole, imageCoord);
	for (int i = gradientSize - 1; i > -1; i--)
	{
		for (size_t j = 0; j < sizeWindow.X / 10; j++)
		{
			wcout << GRADIENT[i];
			Sleep(3);
		}
	}

	imageCoord.X += (4 * sizeWindow.X / 10);
	SetConsoleCursorPosition(hConsole, imageCoord);
	for (int i = 0; i < gradientSize; i++)
	{
		for (size_t j = 0; j < sizeWindow.X / 10; j++)
		{
			wcout << GRADIENT[i];
			Sleep(3);
		}
	}
	OUTPUT_MODE_TEXT;
}

int ShowEndInfo(COORD imageCoord, COORD sizeWindow, char player, size_t textColor)
{
	/*
		Виводить текст. Показує "анімацію"
	*/
	GET_HANDLE(hConsole);
	OUTPUT_MODE_UNICODE;
	SetConsoleTextAttribute(hConsole, (WORD)textColor);

	char textLine1[] = "Press \"Enter\" to return to the main menu.";
	char textLine2[] = "Press \"Escape\" to close the game.";

	imageCoord.X = (sizeWindow.X) / 2 - (strlen(textLine1) + 10) / 2;
	SetConsoleCursorPosition(hConsole, imageCoord);
	wcout << L"░▒▓█ " << textLine1 << L" █▓▒░" << endl;

	imageCoord.X = (sizeWindow.X) / 2 - (strlen(textLine2) + 10) / 2;
	imageCoord.Y += 2;
	SetConsoleCursorPosition(hConsole, imageCoord);
	wcout << L"░▒▓█ " << textLine2 << L" █▓▒░" << endl;

	OUTPUT_MODE_TEXT;
	imageCoord.Y -= 2;
	ShowAnimation(imageCoord, sizeWindow, player);

	imageCoord.Y += 6;
	ShowAnimation(imageCoord, sizeWindow, player);

	int buttonID;
	do
	{
		buttonID = _getch();
		if (buttonID == BUTTON_ENTER)
			return 3;	// RESTART
		if (buttonID == BUTTON_ESCAPE)
			return 4;	// EXIT
	} while (buttonID != BUTTON_ESCAPE && buttonID != BUTTON_ENTER);
	return 0;
}

int ShowEndSaver(char player)
{	/*
		Показує хто виграв або що ніхто не виграв
	*/
	GET_HANDLE(hConsole);
	COORD imageCoord;
	imageCoord.X = 0;
	imageCoord.Y = 2;
	COORD sizeWindow = GetLargestConsoleWindowSize(hConsole);
	if ((player == 'x' || player == '0') && player != ' ')
	{
		imageCoord.X = (sizeWindow.X - (PICTURE_WIDTH + 56)) / 2;
		imageCoord.Y = 2;
		OUTPUT_MODE_UNICODE;
		SetConsoleCursorPosition(hConsole, imageCoord);
		for (size_t i = 0; i < PICTURE_HEIGHT; i++)
		{
			SetCord(imageCoord, i);
			SetConsoleTextAttribute(hConsole, (player == 'x') ? LightBlue : LightPurple);
			for (size_t j = 0; j < PICTURE_WIDTH; j++)
			{
				wcout << ((player == 'x') ? CROSS[i][j] : TOE[i][j]);
			}
			wcout << endl;
		}
		OUTPUT_MODE_TEXT;
	}

	imageCoord.Y = ShowTitle(imageCoord, LightCyan);
	return ShowEndInfo(imageCoord, sizeWindow, player, LightCyan);
}