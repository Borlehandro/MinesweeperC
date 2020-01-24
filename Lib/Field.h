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
	int cellSize; // Todo make it manually or count texture size. You really can use it for
	int cellsCount;
	int bombsCount;

	int upBorder = 0, leftBorder = 0;
	int downBorder, rightBorder;

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
	Field(int _cells, int _bombs, int _cellSize, SDL_Renderer* _renderer); // I will also generate it here

	void handleRightClick(int x, int y);

	void handleLeftClick(int x, int y);

	void preDraw();

    const int getUpBorder() const;

    const int getLeftBorder() const;

    int getDownBorder() const;

    int getRightBorder() const;

};