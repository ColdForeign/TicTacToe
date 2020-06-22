#pragma once
#define MAP_SIZE 3

// Записує в карту символ гравця
void AddToGameMap(SelectedСell* chosenCell, char map[][MAP_SIZE], char symbol);

// Преключає гравця
char PlayerSwitch(char player);

// Запускає функцію вибраної в меню рівня тяжкості(для гри з ШІ)
SelectedСell OtherPlayerWalk(char map[][MAP_SIZE], int difficulty, char player);