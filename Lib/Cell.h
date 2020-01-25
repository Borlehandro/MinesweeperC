#pragma once

#include "SDL.h"
#include "TextureManager.h"

class Cell {

    friend class Field;

private:

    Cell(int _value, SDL_Texture *_openTexture, SDL_Texture *_closeTexture);

    void draw(int i, int j, SDL_Renderer *renderer);

    int open(int i, int j, SDL_Renderer *renderer);

    int mark(int i, int j, SDL_Renderer *renderer);

    void show(int i, int j, SDL_Renderer *renderer);

    bool opened = false;
    int value;
    SDL_Texture *openTexture; // number, or bomb
    SDL_Texture *closeTexture; // empty cell or flag

    static SDL_Texture *flagTexture;
    static SDL_Texture *emptyTexture;
    static SDL_Texture *crossedFlagTexture;

};