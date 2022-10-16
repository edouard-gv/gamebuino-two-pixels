void render() {
  gb.display.clear();

  for (int i = 0; i < gb.display.height(); i++) {
    for (int j = 0; j < gb.display.width(); j++) {
      gb.display.drawPixel(j, i, board[i][j]);
    }
  }
}


