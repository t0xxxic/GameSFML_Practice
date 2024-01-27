#include "src/game.h"
#include <iostream>

int main() {

  // Init sRand
  std::srand(static_cast<unsigned int>(time(NULL)));

  // Init Game Class
  Game game;

  // GameLoop
  while (game.isRunning()) {
    game.update();
    game.render();
  }

  // EndOfApplication
  return 0;
}
