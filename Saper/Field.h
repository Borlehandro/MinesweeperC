#pragma once
#include "Cell.h"
// May be circular inclusion here

class Field {

private:
	const int cellSize = 20; // it can be const, but can be counted
	int cellsCount;
	int bombsCount;

	// Array of cells
	Cell* cells = nullptr;

public:
	Field(int _cells, int _bombs); // I will also generate it here

};

