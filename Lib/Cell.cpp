#include "Cell.h"

void Cell::draw(int i, int j, SDL_Renderer* renderer) {

    //TODO include "20" in macros or get texture size
    TextureManager::getInstance()->ApplySurface(i*20, j*20, closeTexture, renderer);

}