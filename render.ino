int NB_DRIFT_STEPS = 4;
int DOT_DISTANCE = 8;
int HALF_DOT_DISTANCE = 4; // DOT_DISTANCE / 2
int DRIFT_DISTANCE = 2; // DOT_DISTANCE / NB_DRIFT_STEPS

int screen_W = gb.display.width();
int screen_H = gb.display.height();


void render() {
  int shift_W = (screen_W-W*DOT_DISTANCE)/2;
  int shift_H = (screen_H-H*DOT_DISTANCE)/2;
  gb.display.clear();
  for (int x = 0; x < W; x++) {
    for (int y = 0; y < H; y++) {
      int center_x = DOT_DISTANCE*x+HALF_DOT_DISTANCE+shift_W;
      int center_y = DOT_DISTANCE*y+HALF_DOT_DISTANCE+shift_H;
      gb.display.setColor(board[x][y]);
      int shifts = countPositionsIShouldShiftDown(links, W, H, x, y);
      if (isDrifting && shifts > 0) {
        gb.display.drawCircle(center_x, center_y-shifts*DOT_DISTANCE+shifts*driftStep*DRIFT_DISTANCE, HALF_DOT_DISTANCE-1);
      }
      else {
        gb.display.drawCircle(center_x, center_y, HALF_DOT_DISTANCE-1);
        if (x == cursor_x && y == cursor_y) {
          gb.display.drawCircle(center_x, center_y, HALF_DOT_DISTANCE-3);
        }
        if (links[x][y] != Direction::none) {
          gb.display.drawCircle(center_x, center_y, HALF_DOT_DISTANCE-4);
        }
      }
    }
  }

  if (isDrifting) {
    if (driftStep < NB_DRIFT_STEPS) {
      driftStep++;
    }
    else {
      resetLinks(links, W, H);
      isDrifting = false;
      driftStep = 0;
    }
  }

  gb.display.setColor(DARKBLUE);
  gb.display.drawRect(0, 0, screen_W, screen_H);
  gb.display.drawRect(2, 2, screen_W-4, screen_H-4);

  for (int k=0; k < COLOR_COUNT; ++k) {
    int base_x;
    int base_y;
    gb.display.setColor(all_colors[k]);
    gb.display.fillRect(k/3*(screen_W-3), (SCORE_SCALE+1) * (k % 3 + 1) - score[k], 3, score[k]);
  }
}


