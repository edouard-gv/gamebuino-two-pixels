#include <Gamebuino-Meta.h>
#include "TwoPixels_lib/twopixels.h"
Color **board;
Direction **links;
int distributions[5];
Color colorOrder[5];
int SCORE_SCALE = 63;

bool ignoreRelease;

int W=0;
int H=0;

int cursor_x=0;
int cursor_y=0;

bool isLinking=false;
bool isDrifting=false;
int driftStep = 0;

int level = 1;

void setup() {
  gb.begin();

  ignoreRelease = false;

  board = createBoardAtLevel(&W, &H, 1);
  links = createEmptyLinks(W, H);
}

void loop() {
  while(!gb.update());

  input();
  compute();
  render();
}

