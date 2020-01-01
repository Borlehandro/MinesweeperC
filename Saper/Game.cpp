#include "Game.h"

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

	background = textureManager->LoadImage(renderer, "test.bmp");

	return 0;
}

void Game::onRun() {

	SDL_Event event;

	bool quit = false;

		while (!quit) {

			SDL_WaitEvent(&event);

			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			}

			textureManager->ApplySurface(0, 0, background, renderer);
		}

	SDL_Quit();
}

bool Game::isRun() {
	return run;
}
