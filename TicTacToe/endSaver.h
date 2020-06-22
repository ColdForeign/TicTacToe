#pragma once
#include <windows.h>

// ��������� ��� �������� �������
void SetTitleCoord(COORD imageCoord);

// �������� � �����
short ShowTitle(COORD imageCoord, int textColor);

// ������ "�������"
void ShowAnimation(COORD imageCoord, COORD sizeWindow, char player);

// ������� �����, ����� ���� � �������� ShowAnimation
int ShowEndInfo(COORD imageCoord, COORD sizeWindow, char player, size_t textColor);

// ������� ������� �����
int ShowEndSaver(char player);