// Sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "utils.h"
#include "Sudoku.h"

int BOARD[9][9] = 
{ 
	{ 2, 0, 9, 7, 0, 0, 5, 0, 0 },
	{ 0, 0, 4, 0, 9, 0, 1, 0, 0 },
	{ 0, 8, 0, 0, 3, 0, 4, 7, 0 },
	{ 0, 2, 6, 0, 0, 1, 3, 0, 5 },
	{ 0, 5, 0, 0, 0, 0, 0, 2, 0 },
	{ 4, 0, 3, 0, 5, 0, 0, 9, 1 },
	{ 0, 0, 7, 0, 0, 3, 0, 5, 0 },
	{ 3, 0, 2, 0, 1, 5, 0, 8, 7 },
	{ 5, 0, 8, 4, 2, 7, 9, 0, 0 } };

int main()
{
	printf("Testing\n");
	PrintBoard(BOARD[0]);

	Sudoku sudoku;
	bool result = sudoku.SolvePuzzle(BOARD[0]);

	if (result)
	{
		std::cout << "Sudoku solved!\nPress any key to exit.";
		std::cin.ignore();
	}
	else
	{
		std::cout << "Could not solve the puzzle...";
		std::cin.ignore();
	}

	return 0;
}




