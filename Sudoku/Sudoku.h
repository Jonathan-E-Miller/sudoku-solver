#pragma once
class Sudoku
{
public:
	Sudoku();
	~Sudoku();

private:
	bool SolveVertical(int* board, int col, int valueToCheck);
	bool SolveHorizontal(int* board, int row, int valueToCheck);
	bool SolveSquare(int *board, int x, int y, int valueToCheck);
	bool CheckGrid(int* board);
	void FindNextZero(int* board, int* xOut, int* colOut);

public:
	bool SolvePuzzle(int* board);
};

