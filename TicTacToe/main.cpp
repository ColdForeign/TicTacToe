#include <iostream>
#include <windows.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <ctime>

#include "gameBoard.h"
#include "menu.h"
#include "gamePlay.h"
#include "gameLogic.h"
#include "lowMode.h"
#include "endSaver.h"
using namespace std;

#define GET_HANDLE(name) HANDLE (name) = GetStdHandle(STD_OUTPUT_HANDLE)
#define MAP_SIZE 3
#define WIN 0
#define NOTHING 1
#define STANDOFF 2
#define RESTART 3
#define EXIT 4

int main() {
	system("title Tic-Tac-Toe"); //назва консольного вікна
	srand(unsigned(time(nullptr)));

	char map[][MAP_SIZE] =
	{
		{ ' ', ' ', ' ' },
		{ ' ', ' ', ' ' },
		{ ' ', ' ', ' ' }
	};

	int moveResult = NOTHING;
	char player = 'x';
	HideConsoleCursor();
	do
	{
		MenuSettings settings = ShowMenu();
		SelectedСell newCell;
		SelectedСell chosenCell;
		wchar_t** gameGridPoinet = CreateAndFillGameGrid();

		if (!settings.youFirstPlayer && settings.playWithEI)
		{
			newCell = OtherPlayerWalk(map, settings.difficulty, settings.youFirstPlayer);
			map[newCell.X][newCell.Y] = 'x';
			player = PlayerSwitch(player);
		}

		do
		{
			ShowGameGrid(gameGridPoinet, map, 11);
			HighlightSelCell(&chosenCell, map, player, 10);
			AddToGameMap(&chosenCell, map, player);
			if (settings.playWithEI)
			{
				moveResult = GameBoardСheck(map, player);
				if ((moveResult == WIN) || (moveResult == STANDOFF))
					break;
				player = PlayerSwitch(player);
				newCell = OtherPlayerWalk(map, settings.difficulty, settings.youFirstPlayer);

				if (settings.youFirstPlayer)
					map[newCell.X][newCell.Y] = '0';
				else
					map[newCell.X][newCell.Y] = 'x';
			}

			moveResult = GameBoardСheck(map, player);
			if ((moveResult == WIN) || (moveResult == STANDOFF))
				break;
			player = PlayerSwitch(player);

		} while (moveResult == NOTHING);

		DeleteGameGrid(gameGridPoinet);
		if (moveResult != NOTHING)
		{
			system("cls");
			if (moveResult != WIN)
				player = ' ';
			moveResult = ShowEndSaver(player);
		}
		for (size_t x = 0; x < MAP_SIZE; x++)
			for (size_t y = 0; y < MAP_SIZE; y++)
				map[x][y] = ' ';
		system("cls");
	} while (moveResult != EXIT);

	return 0;
}
