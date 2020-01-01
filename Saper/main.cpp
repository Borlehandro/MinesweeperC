#include "SDL.h"
#include <iostream>
#include <string>
#include "TextureManager.h"
#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

int main(int argc, char* argv[]) {

	Game *game = new Game(SCREEN_WIDTH, SCREEN_HEIGHT);

	cout << game->onPreload() << endl;

	game->onRun();

	return 0;
}