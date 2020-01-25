#include "Cell.h"

//Todo make flags counter
//Todo REFACTOR!

SDL_Texture *Cell::flagTexture = nullptr;
SDL_Texture *Cell::emptyTexture = nullptr;
SDL_Texture *Cell::crossedFlagTexture = nullptr;

Cell::Cell(int _value, SDL_Texture* _openTexture, SDL_Texture* _closeTexture):value(_value), openTexture(_openTexture), closeTexture(_closeTexture) {}

void Cell::draw(int i, int j, SDL_Renderer *renderer) {

    //TODO include "20" in macros or get texture size
    TextureManager::getInstance()->ApplySurface(i * 20, j * 20, closeTexture, renderer);
}

int Cell::open(int i, int j, SDL_Renderer *renderer) {

    //TODO include "20" in macros or get texture size
    if (value != -1 && closeTexture != Cell::flagTexture) {
        std::cout << "ok" << std::endl;
        TextureManager::getInstance()->ApplySurface(i * 20, j * 20, openTexture, renderer);
        opened = true;
        return 0;
    }
    else if (closeTexture == Cell::flagTexture) {
        std::cout << "flag" << std::endl;
        closeTexture = Cell::emptyTexture;
        TextureManager::getInstance()->ApplySurface(i * 20, j * 20, closeTexture, renderer);
        return 1;
    } else {
        std::cout << "bomb" << std::endl;
        /*Todo make BOOM here*/
        return 2;
    }
}

void Cell::show(int i, int j, SDL_Renderer* renderer) {
    if(closeTexture != Cell::flagTexture)
    //TODO include "20" in macros or get texture size
        TextureManager::getInstance()->ApplySurface(i * 20, j * 20, openTexture, renderer);
    else if(value!=-1)
        TextureManager::getInstance()->ApplySurface(i * 20, j * 20, crossedFlagTexture, renderer);
}

int Cell::mark(int i, int j, SDL_Renderer *renderer) {
    if(!opened && closeTexture != Cell::flagTexture) {
        closeTexture = Cell::flagTexture;
        TextureManager::getInstance()->ApplySurface(i * 20, j * 20, closeTexture, renderer);
        return 1;
    }
    return 0;
}

