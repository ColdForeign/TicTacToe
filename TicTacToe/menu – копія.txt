#pragma once
#include "menu.h"

int RandColor(size_t firstColor, size_t lastColor)
{
	srand(unsigned(time(nullptr)));
	if (lastColor > 16)
		return 0;
	else
		return rand() % (lastColor - firstColor) + firstColor;
}

void SetCursorInTheCenter(const char* logoLinePointer)
{
	GET_HANDLE(hConsole);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(hConsole, &bufferInfo);
	COORD sizeWindow = GetLargestConsoleWindowSize(hConsole);
	COORD newSize;
	if (sizeWindow.X % 2 != 0)
		sizeWindow.X += 1;

	size_t sizeItem = strlen(logoLinePointer);

	newSize.X = (sizeWindow.X - sizeItem) / 2;
	newSize.Y = bufferInfo.dwCursorPosition.Y;
	SetConsoleCursorPosition(hConsole, newSize);
}

void ShowLogo(int textColor, int backColor)
{
	GET_HANDLE(hConsole);

	ifstream file;

	file.open("menu.txt");
	if (!file.is_open())
	{
		cout << "Error!\nLOGO not found!\n";
		return;
	}
	else
	{
		string logoLine;
		while (!file.eof())
		{
			SetConsoleTextAttribute(hConsole, (WORD)((backColor << 4) | textColor));
			logoLine = "";

			getline(file, logoLine);
			const char* logoLinePointer = logoLine.c_str();
			SetCursorInTheCenter(logoLinePointer);
			cout << logoLine << endl;
		}
	}
	file.close();
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
}

void ShowInformation(int textColor) {
	GET_HANDLE(hConsole);

	ifstream infoFile;

	infoFile.open("menuInformation.txt");
	if (!infoFile.is_open())
	{
		cout << "Error!\nLOGO not found!\n";
		return;
	}
	else
	{
		string logoLine2;
		while (!infoFile.eof())
		{
			SetConsoleTextAttribute(hConsole, textColor);
			logoLine2 = "";

			getline(infoFile, logoLine2);
			const char* logoLinePointer = logoLine2.c_str();
			SetCursorInTheCenter(logoLinePointer);
			cout << logoLine2 << endl;
		}
	}
	infoFile.close();
}

void ShowTextInTheCenter(const MenuItems* item, size_t menuItemID, size_t menuSize, bool selected)
{
	GET_HANDLE(hConsole);											// Отримуємо дескриптор консолі
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;							// Структура з данними экраного буфера
	GetConsoleScreenBufferInfo(hConsole, &bufferInfo);				// Записуємо в цю структуру данні
	COORD sizeWindow = GetLargestConsoleWindowSize(hConsole);		// Массив максимальних розмір консольного вікна
	COORD newSize;													// Массив нових координат курсору виводу
	if (sizeWindow.X % 2 != 0)
		sizeWindow.X += 1;

	size_t sizeItem = strlen(item[menuItemID].itemName);				// Отримуємо розмір елемента меню
	if (selected)
		sizeItem += 4;
	if (sizeItem % 2 != 0)
		sizeItem += 1;

	newSize.X = sizeWindow.X / 2 - sizeItem / 2;					// Нова позиція курсору по горизонталі
	newSize.Y = bufferInfo.dwCursorPosition.Y;						// Нова позиція курсору по вертикалі(не змінилася)
	SetConsoleCursorPosition(hConsole, newSize);					// Нова позиція курсору виводу
}

void ShowMenu(const MenuItems* item, size_t menuItemID, size_t numberItems, int textColor) {
	GET_HANDLE(hConsole);
	bool selected = false;

	for (size_t i = 0; i < numberItems; i++)
	{
		if (i == menuItemID)
		{
			selected = true;
			int sizeItem = strlen(item[i].itemName) + 4;
			SetConsoleTextAttribute(hConsole, textColor);

			ShowTextInTheCenter(item, i, numberItems, selected);
			for (size_t j = 0; j < sizeItem; j++)
				cout << "*";
			cout << endl;

			ShowTextInTheCenter(item, i, numberItems, selected);
			cout << "* " << item[i].itemName << " *\n";

			ShowTextInTheCenter(item, i, numberItems, selected);
			for (size_t j = 0; j < sizeItem; j++)
				cout << "*";
			cout << endl << endl;
		}
		if (i != menuItemID)
		{
			selected = false;

			SetConsoleTextAttribute(hConsole, 15);

			ShowTextInTheCenter(item, i, numberItems, selected);
			cout << item[i].itemName;
			cout << endl << endl;
		}
	}
}

void SetSettings(const MenuItems* item, size_t& menuItemID, MenuSettings* settings, size_t& menuID)
{
	if (menuID == MAIN_MENU)
	{
		if (menuItemID == 0)
		{
			menuID = DIFFICALTY_MENU;
			menuItemID = 0;
			return;
		}
		if (menuItemID == 1)
		{
			settings->playWithEI = false;
			settings->closeMenu = true;
			return;
		}
	}

	if (menuID == DIFFICALTY_MENU)
	{
		if (menuItemID == 3)
		{
			menuID = MAIN_MENU;
			menuItemID = 0;
			return;
		}
		else
		{
			settings->difficulty = menuItemID;
			menuItemID = 0;
			menuID = WHO_WALK_MENU;
			return;
		}
	}

	if (menuID == WHO_WALK_MENU)
	{
		if (menuItemID == 0)
		{
			settings->closeMenu = true;
			return;
		}
		else if (menuItemID == 1)
		{
			settings->youFirstPlayer = false;
			settings->closeMenu = true;
			return;
		}
		else if (menuItemID == 2)
		{
			menuID = DIFFICALTY_MENU;
			menuItemID = 0;
			settings->closeMenu = false;
			return;
		}
	}
}

size_t HighlightMenuItem(const MenuItems* item, MenuSettings* settings, size_t& menuItemID, size_t numberItems, size_t& menuID) {
	GET_HANDLE(hConsole);
	size_t menuSize = numberItems - 1;
	ShowLogo(13, 0);
	ShowMenu(item, menuItemID, numberItems, 13);
	ShowInformation(11);
	int buttonID = _getch();
	if (buttonID == BUTTON_ENTER)
	{
		system("cls");
		SetSettings(item, menuItemID, settings, menuID);
		return BUTTON_ENTER;
	}
	do
	{
		buttonID = _getch();
		if (buttonID == ARROW_DOWN)
		{
			if (menuItemID == menuSize)
				menuItemID = 0;
			else
				menuItemID += 1;
			system("cls");
			ShowLogo(RandColor(1, 15), 0);
			ShowMenu(item, menuItemID, numberItems, 13);
			ShowInformation(11);
		}
		if (buttonID == ARROW_UP)
		{
			if (menuItemID == 0)
				menuItemID = menuSize;
			else
				menuItemID -= 1;
			system("cls");
			ShowLogo(RandColor(1, 15), 0);
			ShowMenu(item, menuItemID, numberItems, 13);
			ShowInformation(11);
		}
		if (buttonID == BUTTON_ENTER)
		{
			if (menuItemID == menuSize)
				exit(0);
			system("cls");
			SetSettings(item, menuItemID, settings, menuID);
			return BUTTON_ENTER;
		}
		if (buttonID == BUTTON_ESCAPE)
		{
			system("cls");
			menuItemID = 0;
			if (menuID == MAIN_MENU)
				continue;
			else
				menuID = MAIN_MENU;
			return BUTTON_ESCAPE;
		}
	} while ((buttonID != BUTTON_ENTER) && (buttonID != BUTTON_ESCAPE));
}

MenuSettings ShowMenu()
{
	size_t menuID = 0;
	size_t menuItemID = 0;
	bool exitFromMenu = false;
	MenuItems mainMenu[]{
		   {"Play with computer"},
		   {"Play with friend"},
		   {"Exit"},
	};
	MenuItems difficultyMenu[]{
		{"Low"},
		{"Medium"},
		{"Hard"},
		{"Go back"},
		{"Exit"},
	};
	MenuItems chooseWhoFirst[]{
		{"I am first"},
		{"Bot first"},
		{"Go back"},
		{"Exit"},
	};

	MenuSettings settings;
	do
	{
		switch (menuID)
		{
		case MAIN_MENU:
			HighlightMenuItem(mainMenu, &settings, menuItemID, SIZE_MAIN_MENU, menuID);
			break;
		case DIFFICALTY_MENU:
			HighlightMenuItem(difficultyMenu, &settings, menuItemID, SIZE_DIFFICALTY_MENU, menuID);
			break;
		case WHO_WALK_MENU:
			HighlightMenuItem(chooseWhoFirst, &settings, menuItemID, SIZE_WHO_WALK_MENU, menuID);
			break;
		}
	} while (!settings.closeMenu);
	return settings;
}