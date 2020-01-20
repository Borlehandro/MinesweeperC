#pragma once
#include "TextureManager.h"
#include "Cell.h"
// May be circular inclusion here

class Field {

private:
	const int cellSize = 20; // it can be const, but can be counted
	int cellsCount;
	int bombsCount;

	// Array of cells
	Cell* cells = nullptr;

	// Textures
	SDL_Texture *zero, *one, *two, *three, *four, *five, *six, *seven, *eight, *empty, *bomb, *flag;

	SDL_Renderer *renderer;

	// Functions inside
	void loadTextures();
	int calculateValue(int index);

public:
	Field(int _cells, int _bombs, SDL_Renderer* _renderer); // I will also generate it here

};

