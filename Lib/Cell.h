#pragma once
#include "SDL.h"
#include "TextureManager.h"
class Cell {

    friend class Field;

private:
    Cell(int _value, SDL_Texture* _openTexture, SDL_Texture* _closeTexture) : 
        value(_value), openTexture(_openTexture), closeTexture(_closeTexture) {}
    void draw(int i, int j, SDL_Renderer* renderer);

    int value;
    SDL_Texture *openTexture; // number, or bomb
    SDL_Texture *closeTexture; // empty cell or flag

};