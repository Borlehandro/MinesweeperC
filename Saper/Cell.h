#pragma once
#include "SDL.h"

class Cell {

    friend class Field;

private:
    Cell(int _value, SDL_Texture* _openTexture, SDL_Texture* _closeTexture) : 
        value(_value), openTexture(_openTexture), closeTexture(_closeTexture) {}

    int value;
    SDL_Texture *openTexture; // number, empty cell or bomb
    SDL_Texture *closeTexture; // empty cell or flag

};