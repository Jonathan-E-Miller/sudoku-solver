#include "stdafx.h"
#include "Sudoku.h"
#include "utils.h"
#include <Windows.h>

#define LEN 9

Sudoku::Sudoku()
{
}


Sudoku::~Sudoku()
{
}

/******************************************************************
** Go through a horizonal row on the board and checks for clashes
**
** board [in]: a pointer to the 2D array map of the board
** row [in]: The row that we wish to check accross
** valueToCheck [in]: The value that we wish to check.
**
** return: True if the valueToCheck is valid
*******************************************************************/
bool Sudoku::SolveHorizontal(int* board, int row, int valueToCheck)
{
	int *rowptr = &board[row * LEN];

	for (int col = 0; col < LEN; col++)
	{
		int value = rowptr[col];

		if ((value == valueToCheck))
		{
			return false;
		}
	}

	return true;
}

/******************************************************************
** Goes down a vertical row on the board and checks for clashes
**
** board [in]: a pointer to the 2D array map of the board
** col [in]: The column number that we wish to check down
** valueToCheck [in]: The value that we wish to check.
**
** return: True if the valueToCheck is valid
*******************************************************************/
bool Sudoku::SolveVertical(int* board, int col, int valueToCheck)
{
	for (int row = 0; row < LEN; row++)
	{
		int value = *(board + row * LEN + col);

		if (value == valueToCheck)
		{
			return false;
		}
	}
	return true;
}

/******************************************************************
** Goes through the square block to ensure that there is not a clash
**
** board [in]: The column we assessing
** col [in]: The row we are assessing
** valueToCheck [in]: The value that we wish to check.
**
** return: True if the valueToCheck is valid
*******************************************************************/
bool Sudoku::SolveSquare(int* board, int col, int row, int valueToCheck)
{
	// get the X,Y coordinates of the top left of the square to check.
	int y = (row / 3) * 3;
	int x = (col / 3) * 3;

	// create limits for loop
	int rowlimit = y + 3;
	int collimit = x + 3;

	// go through each row and column
	for (int row = y; row < rowlimit; row++)
	{
		for (int col = x; col < collimit; col++)
		{
			// get the current value stored at the index location
			// using pointer arithmetic
			int value = *(board + row * LEN + col);

			// Check to see if the value clashes, if so, return false
			if (value == valueToCheck)
			{
				return false;
			}
		}
	}
	// we have got to the end of the function without a clash
	// so return true
	return true;
}

/******************************************************************
** Solves a sudoku puzzle recursively using backtracking
**
** board [in]: The column we assessing
**
** return: True when solved
*******************************************************************/
bool Sudoku::SolvePuzzle(int* board)
{
	// check to see if the grid is complete.
	bool result = CheckGrid(board);
	if (result)
	{
		// grid is complete - return true
		return true;
	}
	// find the X,Y coordinates of the next "0" that we need to find a value for.
	int column;
	int row;
	FindNextZero(board, &column, &row);

	// Presume that the board is not valid
	bool valid = false;
	// go through values 1 to 9
	for (int i = 1; i <= LEN; i++)
	{
		// check to see if the value satisfies the constrains of the sudoku puzzle
		// e.g. 1-9 accorss each horizontal and vertical row as well as square block
		bool horizontalValid = SolveHorizontal(board, row, i);
		bool verticalValid = SolveVertical(board, column, i);
		bool squareValid = SolveSquare(board, column, row, i);

		// if the value has satisfied all constraints then add to the board.
		if (horizontalValid && verticalValid && squareValid)
		{
			// add the value to the board using pointer arithmetic.
			*(board + row * LEN + column) = i;

			UpdateConsoleWithDelay(board, 25);

			// try and solve the next zero
			result = SolvePuzzle(board);

			// we have returned from the recursive call - did we complete successfully?
			if (result == true)
			{
				// we completed successfully so return true.
				return true;
			}

			// we did not complete successfully - so reset the current value back to zero
			*(board + row * LEN + column) = 0;
			UpdateConsoleWithDelay(board, 25);
			// continue with the loop through potential values.
		}
	}
	// we have gone through all potential values and none are valid so return false
	return false;

}
/******************************************************************
** Finds the X and Y coordinates of the next "0" in the board
**
** board [in]: The column we assessing
**
** colOut [out]: ptr to the column value
** rowOut [out]: ptr to the row value
** return: void
*******************************************************************/
void Sudoku::FindNextZero(int* board, int* colOut, int* rowOut)
{
	for (int row = 0; row < LEN; row++)
	{
		for (int column = 0; column < LEN; column++)
		{
			int value = *(board + row * LEN + column);

			// is the value empty
			if (value == 0)
			{
				*colOut = column;
				*rowOut = row;
				return;
			}
		}
	}
}

/******************************************************************
** Goes through the grid and checks to see if it is completed
**
** board [in]: The column we assessing
**
** return: True if no zeros are found - false if zeros are present
*******************************************************************/
bool Sudoku::CheckGrid(int* board)
{
	bool result = true;
	for (int row = 0; row < LEN; row++)
	{
		for (int column = 0; column < LEN; column++)
		{
			int value = *(board + row * LEN + column);

			if (value == 0)
			{
				// zero found return false
				result = false;
			}
		}
	}
	// we have reached the end of the loop without finding a zero
	// we are complete - return true
	return result;
}