#include "Field.h"

#include <random>
#include <ctime>
#include <set>

Field::Field(int _cells, int _bombs, int _cellSize, SDL_Renderer *_renderer) :
        cellsCount(_cells), bombsCount(_bombs), flagsCount(_bombs), unmarkedBombsCount(_bombs), renderer(_renderer),
        cellSize(_cellSize), downBorder(_cells * cellSize + upBorder), rightBorder(_cells * cellSize + leftBorder) {

    // Preload Textures
    loadTextures();

    Cell::size = cellSize;
    Cell::angleY = upBorder;
    Cell::angleX = leftBorder;

    std::cout << "texture map: ";

    for (auto &iter : textureMap) {
        std::cout << iter.second << " ";
    }

    std::cout << std::endl;

    // For each cell in cells array I will write value and load open texture with this number
    // Max number is 8
    // Firstly set all bombs (-1 in value)

    std::mt19937 gen(time(nullptr));
    std::set<int> indexes;

    for (int i = 0; i < cellsCount * cellsCount; ++i)
        indexes.insert(i);

    cells = (Cell *) (calloc(cellsCount * cellsCount, sizeof(Cell)));

    // Make bombs
    for (int i = 0; i < bombsCount; ++i) {

        std::uniform_int_distribution<int> uid(0, indexes.size() - 1);

        int index = uid(gen);

        cells[*std::next(indexes.begin(), index)] = Cell(-1, textureMap[BOMB_CODE], textureMap[EMPTY_CODE]);

        putMarkersAround(*std::next(indexes.begin(), index));

        indexes.erase(std::next(indexes.begin(), index));

    }

    // Init all cells textures
    for (int i = 0; i < cellsCount * cellsCount; ++i) {
        initCellTexture(cells[i]);
    }

    // For debug
    for (int i = 0; i < cellsCount; ++i) {
        for (int j = 0; j < cellsCount; ++j) {
            std::cout << cells[i * cellsCount + j].value << " ";
        }
        std::cout << std::endl;
    }

}

void Field::putMarkersAround(const int &index) {

    // i / n - row
    // i % n - coll

    int i = index / cellsCount;
    int j = index % cellsCount;

#define UP_LEFT cells[(i-1)*cellsCount+(j-1)]
#define UP_CENTRAL cells[(i - 1) * cellsCount + j]
#define UP_RIGHT cells[(i - 1) * cellsCount + (j + 1)]

#define MIDDLE_LEFT cells[i * cellsCount + (j - 1)]
#define MIDDLE_RIGHT cells[i*cellsCount + (j + 1)]

#define DOWN_LEFT cells[(i + 1)*cellsCount + (j - 1)]
#define DOWN_CENTRAL cells[(i + 1)*cellsCount + j]
#define DOWN_RIGHT cells[(i + 1)*cellsCount + (j + 1)]

    //Up
    UP_LEFT.value += (i - 1 >= 0) && (j - 1 >= 0) && (UP_LEFT.value != -1) ? 1 : 0;

    UP_CENTRAL.value += (i - 1 >= 0) && (UP_CENTRAL.value != -1) ? 1 : 0;

    UP_RIGHT.value += (i - 1 >= 0) && (j + 1 < cellsCount) && (UP_RIGHT.value != -1) ? 1 : 0;

    // Mid
    MIDDLE_LEFT.value += (j - 1 >= 0) && (MIDDLE_LEFT.value != -1) ? 1 : 0;

    MIDDLE_RIGHT.value += (j + 1 < cellsCount) && (MIDDLE_RIGHT.value != -1) ? 1 : 0;

    // Down
    DOWN_LEFT.value += (i + 1 < cellsCount) && (j - 1 >= 0) && (DOWN_LEFT.value != -1) ? 1 : 0;

    DOWN_CENTRAL.value += (i + 1 < cellsCount) && (DOWN_CENTRAL.value != -1) ? 1 : 0;

    DOWN_RIGHT.value += (i + 1 < cellsCount) && (j + 1 < cellsCount) && (DOWN_RIGHT.value != -1) ? 1 : 0;

}

void Field::loadTextures() {

    textureMap.emplace(0, TextureManager::getInstance()->LoadImage(renderer, "../Textures/0.bmp"));
    textureMap.emplace(1, TextureManager::getInstance()->LoadImage(renderer, "../Textures/1.bmp"));
    textureMap.emplace(2, TextureManager::getInstance()->LoadImage(renderer, "../Textures/2.bmp"));
    textureMap.emplace(3, TextureManager::getInstance()->LoadImage(renderer, "../Textures/3.bmp"));
    textureMap.emplace(4, TextureManager::getInstance()->LoadImage(renderer, "../Textures/4.bmp"));
    textureMap.emplace(5, TextureManager::getInstance()->LoadImage(renderer, "../Textures/5.bmp"));
    textureMap.emplace(6, TextureManager::getInstance()->LoadImage(renderer, "../Textures/6.bmp"));
    textureMap.emplace(7, TextureManager::getInstance()->LoadImage(renderer, "../Textures/7.bmp"));
    textureMap.emplace(8, TextureManager::getInstance()->LoadImage(renderer, "../Textures/8.bmp"));

    textureMap.emplace(FLAG_CODE, TextureManager::getInstance()->LoadImage(renderer, "../Textures/flag.bmp"));
    textureMap.emplace(BOMB_CODE, TextureManager::getInstance()->LoadImage(renderer, "../Textures/bomb.bmp"));
    textureMap.emplace(EMPTY_CODE, TextureManager::getInstance()->LoadImage(renderer, "../Textures/empty.bmp"));
    textureMap.emplace(CROSSED_FLAG_CODE,
                       TextureManager::getInstance()->LoadImage(renderer, "../Textures/crossed_flag.bmp"));

    Cell::flagTexture = textureMap[FLAG_CODE];
    Cell::emptyTexture = textureMap[EMPTY_CODE];
    Cell::crossedFlagTexture = textureMap[CROSSED_FLAG_CODE];

}

void Field::preDraw() {

    for (int i = 0; i < cellsCount * cellsCount; ++i) {
        std::cout << "Texture: " << cells[i].closeTexture << std::endl;
        cells[i].draw(i % cellsCount, i / cellsCount, renderer);
    }
}

void Field::handleRightClick(int x, int y) {

    int i = (x - leftBorder) / cellSize;
    int j = (y - upBorder) / cellSize;

    std::cout << "I:" << i << " J:" << j << std::endl;

    if (flagsCount > 0) {
        int res = cells[i * cellsCount + j].mark(i, j, renderer);
        if (res == 1 && cells[i * cellsCount + j].value == -1 && unmarkedBombsCount > 0) {
            std::cout << "--" << std::endl;
            unmarkedBombsCount--;
        }

        flagsCount -= res;
    }

    if (unmarkedBombsCount == 0) {
        showAll();
        status = IS_FINISHED;
    }

}

void Field::handleLeftClick(int x, int y) {
    std::cout << "Unmarked: " << unmarkedBombsCount << std::endl;

    int i = (x - leftBorder) / cellSize;
    int j = (y - upBorder) / cellSize;

    std::cout << "I:" << i << " J:" << j << std::endl;
    int res = cells[i * cellsCount + j].open(i, j, renderer);
    if (res != 2) {
        flagsCount += res;
        if (res == 1 && cells[i * cellsCount + j].value == -1 && unmarkedBombsCount < bombsCount) {
            std::cout << "++" << std::endl;
            unmarkedBombsCount++;
        }

    } else {
        showAll();
        status = IS_ABORTED;
    }

}

void Field::initCellTexture(Cell &cell) {
    std::cout << "textureMap[cell->value]: " << textureMap[cell.value] << " val: " << cell.value << std::endl;

    cell.openTexture = textureMap[cell.value];
    cell.closeTexture = textureMap[EMPTY_CODE];

}

void Field::showAll() {
    for (int k = 0; k < cellsCount; ++k)
        for (int t = 0; t < cellsCount; t++)
            cells[k * cellsCount + t].show(k, t, renderer);
}

const int Field::getUpBorder() const {
    return upBorder;
}

const int Field::getLeftBorder() const {
    return leftBorder;
}

const int Field::getDownBorder() const {
    return downBorder;
}

const int Field::getRightBorder() const {
    return rightBorder;
}

unsigned int Field::getStatus() {
    return status;
}