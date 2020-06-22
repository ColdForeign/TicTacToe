#pragma once
#include <windows.h>

// Кординати для великого надпису
void SetTitleCoord(COORD imageCoord);

// Виводить з файлу
short ShowTitle(COORD imageCoord, int textColor);

// Показує "анімацію"
void ShowAnimation(COORD imageCoord, COORD sizeWindow, char player);

// Показую текст, звязує себе з функцією ShowAnimation
int ShowEndInfo(COORD imageCoord, COORD sizeWindow, char player, size_t textColor);

// Показую кінцевий екран
int ShowEndSaver(char player);