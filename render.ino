int NB_DRIFT_STEPS = 4;
int DOT_DISTANCE = 8;
int HALF_DOT_DISTANCE = 4; // DOT_DISTANCE / 2
int DRIFT_DISTANCE = 2; // DOT_DISTANCE / NB_DRIFT_STEPS

int screen_W = gb.display.width();
int screen_H = gb.display.height();


void render() {
  gb.display.clear();
  for (int x = 0; x < W; x++) {
    for (int y = 0; y < H; y++) {
      int center_x = DOT_DISTANCE*x+HALF_DOT_DISTANCE-1;
      int center_y = DOT_DISTANCE*y+HALF_DOT_DISTANCE-1;
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

  int pos_y = 0;
  for (int k=0; k < COLOR_COUNT; ++k) {
    gb.display.setColor(colorOrder[k]);
    gb.display.fillRect(72, pos_y, 4, distributions[k]);
    pos_y += distributions[k];
  }

  int pos_x = 0;
  for (int s=0; s < COLOR_COUNT*3; ++s) {
    gb.display.setColor(all_colors[s/3]);
    if (score[s]) {
      switch (s % 3) {
        case (0): gb.display.drawRoundRect(pos_x, 58, 3, 5, 1); break;
        case (1): 
          gb.display.drawRoundRect(pos_x, 58, 3, 5, 1);
          gb.display.drawFastVLine(pos_x+1, 60, 2);
          break;
        case (2): gb.display.fillRoundRect(pos_x, 58, 3, 5, 1); break;
      }
      pos_x += (pos_x == 30 || pos_x == 54 ? 4 : 5);
    }    
  }
}


