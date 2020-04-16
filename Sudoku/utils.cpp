#include "stdafx.h"
#include "utils.h"
#include <iostream>
#include <Windows.h>
void PrintBoard(int* board)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int value = *(board + i * 9 + j);
			printf("%d\t", value);
		}
		printf("\n");
	}
}
void Clear()
{
	system("cls");
}

void UpdateConsoleWithDelay(int* board, int delay)
{
	// update the console output
	Clear();
	PrintBoard(board);
	Sleep(delay);
}