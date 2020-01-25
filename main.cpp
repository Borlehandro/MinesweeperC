#include <iostream>
#include <string>
#include "Lib/Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

int main(int argc, char *argv[]) {

    Game *game = new Game(SCREEN_WIDTH, SCREEN_HEIGHT);

    cout << game->preload() << endl;

    game->run();

    return 0;
}