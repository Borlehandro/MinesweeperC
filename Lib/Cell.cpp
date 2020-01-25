#include "Cell.h"

//Todo make flags counter
//Todo REFACTOR!

SDL_Texture *Cell::flagTexture = nullptr;
SDL_Texture *Cell::emptyTexture = nullptr;
SDL_Texture *Cell::crossedFlagTexture = nullptr;
int Cell::size = 0;
int Cell::angleX = 0;
int Cell::angleY = 0;

Cell::Cell(int _value, SDL_Texture* _openTexture, SDL_Texture* _closeTexture):value(_value), openTexture(_openTexture), closeTexture(_closeTexture) {}

void Cell::draw(int i, int j, SDL_Renderer *renderer) {

    TextureManager::getInstance()->ApplySurface(i * Cell::size + angleX, j * Cell::size + angleY, closeTexture, renderer);
}

int Cell::open(int i, int j, SDL_Renderer *renderer) {

    if (value != -1 && closeTexture != Cell::flagTexture) {
        std::cout << "ok" << std::endl;
        TextureManager::getInstance()->ApplySurface(i * Cell::size + angleX, j * Cell::size + angleY, openTexture, renderer);
        opened = true;
        return 0;
    }
    else if (closeTexture == Cell::flagTexture) {
        std::cout << "flag" << std::endl;
        closeTexture = Cell::emptyTexture;
        TextureManager::getInstance()->ApplySurface(i * Cell::size + angleX, j * Cell::size + angleY, closeTexture, renderer);
        return 1;
    } else {
        std::cout << "bomb" << std::endl;
        /*Todo make BOOM here*/
        return 2;
    }
}

void Cell::show(int i, int j, SDL_Renderer* renderer) {

    if(closeTexture != Cell::flagTexture)
        TextureManager::getInstance()->ApplySurface(i * Cell::size + angleX, j * Cell::size + angleY, openTexture, renderer);
    else if(value!=-1)
        TextureManager::getInstance()->ApplySurface(i * Cell::size + angleX, j * Cell::size + angleY, crossedFlagTexture, renderer);
}

int Cell::mark(int i, int j, SDL_Renderer *renderer) {
    if(!opened && closeTexture != Cell::flagTexture) {
        closeTexture = Cell::flagTexture;
        TextureManager::getInstance()->ApplySurface(i * Cell::size + angleX, j * Cell::size + angleY, closeTexture, renderer);
        return 1;
    }
    return 0;
}