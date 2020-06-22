#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <conio.h>
#include <ctime>
using namespace std;

#define GET_HANDLE(name) HANDLE (name) = GetStdHandle(STD_OUTPUT_HANDLE)

#define ARROW_UP 72
#define ARROW_DOWN 80
#define BUTTON_ENTER 13
#define BUTTON_ESCAPE 27

#define SIZE_MAIN_MENU 3
#define SIZE_DIFFICALTY_MENU 5
#define SIZE_WHO_WALK_MENU 4

#define MAIN_MENU 0
#define DIFFICALTY_MENU 1
#define WHO_WALK_MENU 2

struct MenuItems
{
	char itemName[30] = " ";
};

struct MenuSettings
{
	int difficulty = 0; // 0 - low, 1 - medium, 2 - hard
	bool youFirstPlayer = true;
	bool playWithEI = true;
	bool closeMenu = false;
};

//Функція рандомить номер кольору в межах firstColor і lastColor і повертає його
int RandColor(size_t firstColor, size_t lastColor);

// Вірівнює вивід пункта меню по центру консольного вікна
void ShowTextInTheCenter(const MenuItems* item, size_t menuId, size_t menuSize, bool selected);

//Ставить крсор в потрібне місце для виведення "логотипу" по центру.
void SetCursorInTheCenter(const char* logoLinePointer);

// Виводить "логотип"
void ShowLogo(int textColor, int backColor);

// Показує вибране меню. Приймеє структуру з пунктами, номер елмента яккий треба виділити,
// кіл-ть на колір.
void ShowMenu(const MenuItems* item, size_t menuId, size_t numberItems, int textColor);

// Показує меню.
MenuSettings ShowMenu();

// Функція яка дає можливість керувати стрілками, повертає вибраний пункт меню
size_t HighlightMenuItem(const MenuItems* item, MenuSettings* settings, size_t& menuItemID, size_t numberItems, size_t& menuID);

// Встановлює налаштування взалежності від вибраного в меню.
void SetSettings(const MenuItems* item, size_t& menuItemID, MenuSettings* settings, size_t& menuID);

// Виводить інформацію про управління меню.
void ShowInformation(int textColor);
