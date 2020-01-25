#pragma once

#include "TextureManager.h"
#include "Field.h"

#define CELL_SIZE 75

class Game {

private:
    //Private functions
    void parseEvent(SDL_Event &event);

    bool isInField(int x, int y);

    //Functional objects
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    TextureManager *textureManager = TextureManager::getInstance();

    //Windows Params
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;

    //Resources
    SDL_Texture *background = nullptr;
    SDL_Texture *blueScreen = nullptr;
    SDL_Texture *winScreen = nullptr;

    //Field
    Field *field = nullptr;

    //Status
    bool isRunning = true;

public:
    Game(int widht, int height) :
            SCREEN_WIDTH(widht),
            SCREEN_HEIGHT(height) {};

    int preload();

    void predraw();

    void run();

    bool isRun();
};