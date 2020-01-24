#pragma once

#include <unordered_map>
#include "TextureManager.h"
#include "Cell.h"
// May be circular inclusion here

class Field {

    #define BOMB_CODE -1
    #define FLAG_CODE -2
    #define EMPTY_CODE -3

private:
	const int cellSize = 20; // Todo make it const or count texture size
	int cellsCount;
	int bombsCount;

	// Array of cells
	Cell* cells = nullptr;

	// Textures
	std::unordered_map<int, SDL_Texture*> textureMap;

	SDL_Renderer *renderer;

	// Functions inside
	void loadTextures();
	void putMarkersAround(const int &index);
	void initCellTexture(Cell &cell);

public:
	Field(int _cells, int _bombs, SDL_Renderer* _renderer); // I will also generate it here
	void preDraw();

};