#pragma once
#include "SDL.h"
#include "TextureManager.h"

class Game {
	private:
		//Private functions
		void parseEvent(SDL_Event &event);

		//Functional objects
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		TextureManager* textureManager = TextureManager::getInstance();

		//Windows Params
		const int SCREEN_WIDTH;
		const int SCREEN_HEIGHT;

		//Resources
		SDL_Texture* background = nullptr;

		//Status 
		bool run = true;

	public:
		// Game() : SCREEN_WIDTH(), SCREEN_HEIGHT() {} ;
		Game(int widht, int height) : 
			SCREEN_WIDTH(widht), 
			SCREEN_HEIGHT(height) {};

		int onPreload();
		void onRun();
		bool isRun();
};