#pragma once

#include <unordered_map>
#include "TextureManager.h"
#include "Cell.h"
// May be circular inclusion here

class Field {

    #define BOMB_CODE -1
    #define FLAG_CODE -2
    #define EMPTY_CODE -3
    #define CROSSED_FLAG_CODE -4

private:
	const int cellSize;
	const int cellsCount;
	const int bombsCount;
	int flagsCount;
	int unmarkedBombsCount;

	const int upBorder = 65, leftBorder = 125;
	const int downBorder, rightBorder;

	// Cells matrix
	Cell* cells = nullptr;

	// Textures
	std::unordered_map<int, SDL_Texture*> textureMap;

	SDL_Renderer *renderer;

    unsigned int status = IS_PAYING;

	// Functions inside
	void loadTextures();
	void putMarkersAround(const int &index);
	void initCellTexture(Cell &cell);
	void showAll();

public:

    const static unsigned int IS_PAYING = 0;
    const static unsigned int IS_FINISHED = 1;
    const static unsigned int IS_ABORTED = 2;

	Field(int _cells, int _bombs, int _cellSize, SDL_Renderer* _renderer); // I will also generate it here

	void handleRightClick(int x, int y);

	void handleLeftClick(int x, int y);

	void preDraw();

	unsigned int getStatus();

    const int getUpBorder() const;
    const int getLeftBorder() const;
    const int getDownBorder() const;
    const int getRightBorder() const;

};