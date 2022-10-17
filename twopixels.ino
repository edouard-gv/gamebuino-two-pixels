#include <Gamebuino-Meta.h>
#include "TwoPixels_lib/twopixels.h"
Color **board;

bool red;
bool ignoreRelease;

int W=0;
int H=0;

void setup() {
  gb.begin();

  ignoreRelease = false;

  board = createBoardAtLevel(&W, &H, 1);
}

void loop() {
  while(!gb.update());

  input();
  compute();
  render();
}

