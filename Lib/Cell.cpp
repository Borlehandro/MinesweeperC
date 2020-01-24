#include "Cell.h"

//Todo make flags counter
//Todo REFACTOR!

void Cell::draw(int i, int j, SDL_Renderer *renderer) {

    //TODO include "20" in macros or get texture size
    TextureManager::getInstance()->ApplySurface(i * 20, j * 20, closeTexture, renderer);
}

int Cell::open(int i, int j, SDL_Texture *flag, SDL_Texture *empty, SDL_Renderer *renderer) {

    //TODO include "20" in macros or get texture size
    if (value != -1 && closeTexture != flag) {
        std::cout << "ok" << std::endl;
        TextureManager::getInstance()->ApplySurface(i * 20, j * 20, openTexture, renderer);
        opened = true;
        return 0;
    }
    else if (closeTexture == flag) {
        std::cout << "flag" << std::endl;
        closeTexture = empty;
        TextureManager::getInstance()->ApplySurface(i * 20, j * 20, closeTexture, renderer);
        return 1;
    } else {
        std::cout << "bomb" << std::endl;
        /*Todo make BOOM here*/
        return 2;
    }
}

void Cell::show(int i, int j, SDL_Renderer* renderer) {
    //TODO include "20" in macros or get texture size
    TextureManager::getInstance()->ApplySurface(i * 20, j * 20, openTexture, renderer);
}

int Cell::mark(int i, int j, SDL_Texture *flag, SDL_Renderer *renderer) {
    if(!opened && closeTexture!=flag) {
        closeTexture = flag;
        TextureManager::getInstance()->ApplySurface(i * 20, j * 20, closeTexture, renderer);
        return 1;
    }
    return 0;
}