#include "Game.h"
#include <SDL2/SDL.h>

int Game::onPreload() {

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 2;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED
                                              | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return 3;
    }

    background = textureManager->LoadImage(renderer, "../Textures/test.bmp");

    field = new Field(5, 3, CELL_SIZE, renderer);

    return 0;
}

void Game::onPredraw() {

    textureManager->ApplySurface(0, 0, background, renderer);
    field->preDraw();
}

void Game::onRun() {

    //Predraw some textures
    onPredraw();

    SDL_Event event;

    while (run) {

        SDL_WaitEvent(&event);
        parseEvent(event);

    }

    SDL_Quit();
}

bool Game::isRun() {
    return run;
}

void Game::parseEvent(SDL_Event &event) {

    switch (event.type) {

        case (SDL_QUIT):
            run = false;
            break;

        case (SDL_MOUSEBUTTONDOWN):
            switch (event.button.button) {

                case (SDL_BUTTON_LEFT):
                    if (isInField(event.button.x, event.button.y)) {

                        std::cout << "Mouse left" << std::endl;
                        field->handleLeftClick(event.button.x, event.button.y);
                    }

                    break;

                case (SDL_BUTTON_RIGHT):
                    if (isInField(event.button.x, event.button.y)) {

                        std::cout << "Mouse right" << std::endl;
                        field->handleRightClick(event.button.x, event.button.y);
                    }
                    break;
            }

            break;
    }
}

bool Game::isInField(int x, int y) {

    return x > field->getLeftBorder() && y > field->getUpBorder() && x < field->getRightBorder()
        && y < field->getDownBorder();
}
