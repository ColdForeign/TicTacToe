#pragma once
#include <iostream>
#include <ctime>
#include "gameBoard.h"
#include "pictures.cpp"
using namespace std;

#define GET_HANDLE(name) HANDLE (name) = GetStdHandle(STD_OUTPUT_HANDLE)
#define PICTURE_HEIGHT 5
#define PICTURE_WIDTH 11
#define MAP_SIZE 3	

Selected—ell RandomCoord(char map[][MAP_SIZE], char player);
