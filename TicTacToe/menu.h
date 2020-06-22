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

//������� ��������� ����� ������� � ����� firstColor � lastColor � ������� ����
int RandColor(size_t firstColor, size_t lastColor);

// ³����� ���� ������ ���� �� ������ ����������� ����
void ShowTextInTheCenter(const MenuItems* item, size_t menuId, size_t menuSize, bool selected);

//������� ����� � ������� ���� ��� ��������� "��������" �� ������.
void SetCursorInTheCenter(const char* logoLinePointer);

// �������� "�������"
void ShowLogo(int textColor, int backColor);

// ������ ������� ����. ������ ��������� � ��������, ����� ������� ����� ����� �������,
// ��-�� �� ����.
void ShowMenu(const MenuItems* item, size_t menuId, size_t numberItems, int textColor);

// ������ ����.
MenuSettings ShowMenu();

// ������� ��� �� ��������� �������� ��������, ������� �������� ����� ����
size_t HighlightMenuItem(const MenuItems* item, MenuSettings* settings, size_t& menuItemID, size_t numberItems, size_t& menuID);

// ���������� ������������ ���������� �� ��������� � ����.
void SetSettings(const MenuItems* item, size_t& menuItemID, MenuSettings* settings, size_t& menuID);

// �������� ���������� ��� ��������� ����.
void ShowInformation(int textColor);
