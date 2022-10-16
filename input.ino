void input() {
  int H = gb.display.height();
  int W = gb.display.width();

  if (gb.buttons.repeat(BUTTON_A, 0)) {
    nextBoard(board, newBoard, H, W);
    Color **tmp = board;
    board = newBoard;
    newBoard = tmp;
  }

  if (gb.buttons.held(BUTTON_B, 25)) {
    initializeBoard(board, H, W);
    ignoreRelease = true;
  }

  if (gb.buttons.released(BUTTON_B)) {
    //copyWorld(savedWorld, world, H, W);
    if (!ignoreRelease) {
      red = !red;
    }
    else {
      ignoreRelease = false;
    }
  }
}


