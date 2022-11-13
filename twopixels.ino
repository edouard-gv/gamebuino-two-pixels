#include <Gamebuino-Meta.h>
#include "TwoPixels_lib/twopixels.h"
Color **board;
Direction **links;
int W=0;
int H=0;

int cursor_x=0;
int cursor_y=0;

int distributions[COLOR_COUNT];
Color colorOrder[COLOR_COUNT];
bool score[COLOR_COUNT*3];
const int SCORE_SCALE = 63;


bool isLinking=false;
bool hasChanged=true;
bool isDrifting=false;
int driftStep = 0;

int level = 1;

bool ignoreRelease;

const int SAVE_GAME_IS_SAVED = 0;
const int SAVE_SCORES = 1;
const int SAVE_BOARD = 2; //UP TO 1+W

void save() {
  gb.save.set(SAVE_GAME_IS_SAVED, (int32_t)true);
  gb.save.set(SAVE_SCORES, score, COLOR_COUNT*3*sizeof(bool));
  for (int x = 0; x < W; ++x) {
    gb.save.set(SAVE_BOARD+x, board[x], H*sizeof(Color)); 
  }
}


void load() {
  if ((bool)gb.save.get(SAVE_GAME_IS_SAVED)) {
    gb.save.get(SAVE_SCORES, score, COLOR_COUNT*3*sizeof(bool));
    for (int x = 0; x < W; ++x) {
      gb.save.get(SAVE_BOARD+x, board[x], H*sizeof(Color)); 
    }
  }
}

void setup() {
  gb.begin();

  ignoreRelease = false;

  board = createBoardAtLevel(&W, &H, level);
  links = createEmptyLinks(W, H);
  resetScore(score);

  load();
}

void loop() {
  while(!gb.update());

  input();
  compute();
  render();
}

