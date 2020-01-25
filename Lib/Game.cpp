#include "Game.h"
#include "TextWriter.h"
#include <SDL2/SDL.h>

#define LOSE_TEXT_X 10
#define LOSE_TEXT_Y 300
#define WIN_TEXT_X 10
#define WIN_TEXT_Y 200

#define LOSE_COUNT_TEXT_X 300
#define LOSE_COUNT_TEXT_Y 350
#define WIN_COUNT_TEXT_X 200
#define WIN_COUNT_TEXT_Y 250

#define TIMER_COUNT 5
#define CELLS_COUNT 5
#define BOMBS_COUNT 5
#define DELAY_STEP 1000

#define WHITE SDL_Color({255,255,255})
#define GREEN SDL_Color({0,255,0})

int Game::preload() {

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

    background = textureManager->LoadImage(renderer, "../Textures/background.bmp");
    blueScreen = textureManager->LoadImage(renderer, "../Textures/blue_screen.bmp");
    winScreen = textureManager->LoadImage(renderer, "../Textures/win.bmp");

    field = new Field(CELLS_COUNT, BOMBS_COUNT, CELL_SIZE, renderer);

    return 0;
}

void Game::predraw() {

    textureManager->ApplySurface(0, 0, background, renderer);

    field->preDraw();
}

void Game::run() {

    //Predraw some textures
    predraw();

    SDL_Event event;

    while (isRunning) {

        SDL_WaitEvent(&event);
        parseEvent(event);

        if (field->getStatus() == Field::IS_ABORTED) {
            SDL_Delay(DELAY_STEP);
            field = new Field(CELLS_COUNT, BOMBS_COUNT - 2, CELL_SIZE, renderer);

            SDL_RenderClear(renderer);
            for (int i = 0; i < TIMER_COUNT; ++i) {
                textureManager->ApplySurface(0, 0, blueScreen, renderer);
                TextWriter::getInstance()->renderText("You FAILED this game! New game will start in... ", LOSE_TEXT_X,
                                                      LOSE_TEXT_Y, WHITE, renderer);
                TextWriter::getInstance()->renderText(std::to_string(TIMER_COUNT - i), LOSE_COUNT_TEXT_X,
                                                      LOSE_COUNT_TEXT_Y, WHITE, renderer);
                SDL_Delay(DELAY_STEP);
                SDL_RenderClear(renderer);

            }

            predraw();
        } else if (field->getStatus() == Field::IS_FINISHED) {
            SDL_Delay(DELAY_STEP);
            field = new Field(CELLS_COUNT, BOMBS_COUNT + 5, CELL_SIZE, renderer);

            SDL_RenderClear(renderer);
            for (int i = 0; i < TIMER_COUNT; ++i) {
                textureManager->ApplySurface(0, 0, winScreen, renderer);
                TextWriter::getInstance()->renderText("You WON this game! New game will start in... ", WIN_TEXT_X,
                                                      WIN_TEXT_Y, GREEN, renderer);
                TextWriter::getInstance()->renderText(std::to_string(TIMER_COUNT - i), WIN_COUNT_TEXT_X,
                                                      WIN_COUNT_TEXT_Y, GREEN, renderer);
                SDL_Delay(DELAY_STEP);
                SDL_RenderClear(renderer);

            }

            predraw();
        }

    }

    SDL_Quit();
}

bool Game::isRun() {
    return isRunning;
}

void Game::parseEvent(SDL_Event &event) {

    switch (event.type) {

        case (SDL_QUIT):
            isRunning = false;
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