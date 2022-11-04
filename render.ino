int NB_DRIFT_STEPS = 5;

void render() {
  gb.display.clear();
  for (int x = 0; x < W; x++) {
    for (int y = 0; y < H; y++) {
      gb.display.setColor(board[x][y]);
      if (isDrifting && links[x][y] != Direction::none) {
        gb.display.drawCircle(10*x+5, 10*y-5+2*driftStep, 4);
      }
      else {
        gb.display.drawCircle(10*x+5, 10*y+5, 4);
        if (x == cursor_x && y == cursor_y) {
          gb.display.drawCircle(10*x+5, 10*y+5, 2);
        }
        if (links[x][y] != Direction::none) {
          gb.display.drawCircle(10*x+5, 10*y+5, 1);
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


