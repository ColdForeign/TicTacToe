#pragma once
#define MAP_SIZE 3
#define WIN 0
#define NOTHING 1
#define STANDOFF 2

bool HorizontalCheck(char map[][MAP_SIZE], char player);	// Перевірка ігровго поля по горизонталі
bool VerticalCheck(char map[][MAP_SIZE], char player);		// Перевірка ігровго поля по вертикалі
bool DiagonalCheck(char map[][MAP_SIZE], char player);		// Перевірка ігровго поля по діагоналям
int GameBoardСheck(char map[][MAP_SIZE], char player);		// Аналізує результати 3-ох поперадніх функцій.