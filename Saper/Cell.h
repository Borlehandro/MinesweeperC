#pragma once
#include "SDL.h"

class Cell {

    friend class Field;

private:
    int value;
    SDL_Texture* openTexture; // number, empty cell or bomb
    SDL_Texture* closeTexture; // empty cell or flag

};