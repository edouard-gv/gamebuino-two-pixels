int NB_DRIFT_STEPS = 5;
int DOT_DISTANCE = 10;
int HALF_DOT_DISTANCE = 5; // DOT_DISTANCE / 2
int DRIFT_DISTANCE = 2; // DOT_DISTANCE / NB_DRIFT_STEPS

void render() {
  gb.display.clear();
  for (int x = 0; x < W; x++) {
    for (int y = 0; y < H; y++) {
      int center_x = DOT_DISTANCE*x+HALF_DOT_DISTANCE;
      int center_y = DOT_DISTANCE*y+HALF_DOT_DISTANCE;
      gb.display.setColor(board[x][y]);
      int shifts = countPositionsIShouldShiftDown(links, W, H, x, y);
      if (isDrifting && shifts > 0) {
        gb.display.drawCircle(center_x, center_y-shifts*DOT_DISTANCE+shifts*driftStep*DRIFT_DISTANCE, 4);
      }
      else {
        gb.display.drawCircle(center_x, center_y, 4);
        if (x == cursor_x && y == cursor_y) {
          gb.display.drawCircle(center_x, center_y, 2);
        }
        if (links[x][y] != Direction::none) {
          gb.display.drawCircle(center_x, center_y, 1);
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
}


