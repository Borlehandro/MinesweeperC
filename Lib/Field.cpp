#include "Field.h"

#include <random>
#include <time.h>
#include <set>

Field::Field(int _cells, int _bombs, SDL_Renderer *_renderer) : 
	cellsCount(_cells), bombsCount(_bombs), renderer(_renderer) {

	// Preload Textures
	loadTextures();

	// For each cell in cells array I will write value and load open texture with this number
	// Max number is 8
	// Firstly set all bombs (-1 in value)

	std::mt19937 gen(time(0));
	std::set<int> indexes;

	for (int i = 0; i < cellsCount * cellsCount; ++i)
		indexes.insert(i);

	cells = (Cell*)calloc(cellsCount * cellsCount, sizeof(Cell));

	for (int i = 0; i < bombsCount; ++i) {

		std::uniform_int_distribution<int> uid(0, indexes.size()-1);

		int index = uid(gen);

		cells[*std::next(indexes.begin(), index)] = Cell(-1, bomb, empty);

		indexes.erase(std::next(indexes.begin(), index));

	}

	// Put numbers in cells
	for (int i = 0; i < cellsCount * cellsCount; ++i) {
		if (cells[i].value == 0)
			cells[i].value = calculateValue(i);
	}

	// For debug
	for (int i = 0; i < cellsCount; ++i) {
		for (int j = 0; j < cellsCount; ++j) {
			std::cout << cells[i * cellsCount + j].value << " ";
		}
		std::cout << std::endl;
	}

}

int Field::calculateValue(int index) {
	
	int count = 0;

	int i = index / cellsCount;
	int j = index % cellsCount;

	// i / n - row
	// i % n - coll

	// Up
	count += (i - 1 >= 0 && j - 1 >= 0) ? (cells[(i-1)*cellsCount+(j-1)].value == -1) : 0;
	count += (i - 1 >= 0) ? (cells[(i - 1) * cellsCount + j].value == -1) : 0;
	count += (i - 1 >= 0 && j + 1 < cellsCount) ? (cells[(i - 1) * cellsCount + (j + 1)].value == -1) : 0;

	// Mid
	count += (j - 1 >= 0) ? (cells[i * cellsCount + (j - 1)].value == -1) : 0;
	count += (j + 1 < cellsCount) ? (cells[i*cellsCount + (j + 1)].value == -1) : 0;

	// Down
	count += (i + 1 < cellsCount && j - 1 >= 0) ? (cells[(i + 1)*cellsCount + (j - 1)].value == -1) : 0;
	count += (i + 1 < cellsCount) ? (cells[(i + 1)*cellsCount + j].value == -1) : 0;
	count += (i + 1 < cellsCount && j + 1 < cellsCount) ? (cells[(i + 1)*cellsCount + (j + 1)].value == -1) : 0;

	return count;
}

void Field::loadTextures() {

	zero = TextureManager::getInstance()->LoadImage(renderer, "0.bmp");
	one = TextureManager::getInstance()->LoadImage(renderer, "1.bmp");
	two = TextureManager::getInstance()->LoadImage(renderer, "2.bmp");
	three = TextureManager::getInstance()->LoadImage(renderer, "3.bmp");
	four = TextureManager::getInstance()->LoadImage(renderer, "4.bmp");
	five = TextureManager::getInstance()->LoadImage(renderer, "5.bmp");
	six = TextureManager::getInstance()->LoadImage(renderer, "6.bmp");
	seven = TextureManager::getInstance()->LoadImage(renderer, "7.bmp");
	eight = TextureManager::getInstance()->LoadImage(renderer, "8.bmp");
	
	flag = TextureManager::getInstance()->LoadImage(renderer, "flag.bmp");
	bomb = TextureManager::getInstance()->LoadImage(renderer, "bomb.bmp");
	empty = TextureManager::getInstance()->LoadImage(renderer, "empty.bmp");

}