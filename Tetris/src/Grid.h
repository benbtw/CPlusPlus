#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
	Grid();
	void Initialize();
	void print();
	void Draw();
	bool isCellOutside(int row, int col);
	bool isCellEmpty(int row, int col);
	int ClearFullRows();
	int grid[20][10];
private:
	bool isRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
	int numRows;
	int numCols;
	int cellSize;
	std::vector<Color> colors;
};

