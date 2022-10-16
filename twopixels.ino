#include <Gamebuino-Meta.h>
#include "TwoPixels_lib/twopixels.h"
Color **board;
Color **newBoard;
//Color **savedWorld;

bool red;
bool ignoreRelease;

void setup() {
  gb.begin();

  red = true;
  ignoreRelease = false;
  const int height = gb.display.height();
  const int width = gb.display.width();

  board = new Color*[height];
  newBoard = new Color*[height];
  //savedWorld = new bool*[height];

  for (int i=0; i < height; i++) {
    board[i] = new Color[width];
    newBoard[i] = new Color[width];
    //savedWorld[i] = new bool[width];
  }

  initializeBoard(board, height, width);

  //copyWorld(world, savedWorld, height, width);

  //TODO: This must be put somewhere!
  /*
  for (int i = 0; i < HEIGHT; i++) {
    delete world[i];
    delete newWorld[i];
  }
  delete world;
  delete newWorld;
  delete savedWorld;
  */
}

void loop() {
  while(!gb.update());

  input();
  compute();
  render();
}

