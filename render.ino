void render() {
  gb.display.clear();

  for (int x = 0; x < W; x++) {
    for (int y = 0; y < H; y++) {
      gb.display.setColor(board[x][y]);
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


