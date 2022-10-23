void resetLevel() {
  deleteBoard(board, W);
  deleteLinks(links, W);
  board = createBoardAtLevel(&W, &H, level);
  links = createEmptyLinks(W, H);
  cursor_x = 0;
  cursor_y = 0;
}

void input() {

  int i = random(1,14);

    if (gb.buttons.held(BUTTON_A, 0)) {
      isLinking = true;
    }

    if (gb.buttons.released(BUTTON_A)) {
      isLinking = false;
      consumeLinks(board, links, W, H);
      resetLinks(links, W, H);
    }

    if (!isLinking) {
      if (gb.buttons.pressed(BUTTON_UP)) {
          moveIfLegit(board, W, H, &cursor_x, &cursor_y, Direction::up_dir);
      }
      if (gb.buttons.pressed(BUTTON_RIGHT)) {
          moveIfLegit(board, W, H, &cursor_x, &cursor_y, Direction::right_dir);
      }
      if (gb.buttons.pressed(BUTTON_DOWN)) {
          moveIfLegit(board, W, H, &cursor_x, &cursor_y, Direction::down_dir);
      }
      if (gb.buttons.pressed(BUTTON_LEFT)) {
          moveIfLegit(board, W, H, &cursor_x, &cursor_y, Direction::left_dir);
      }
    }

    if (isLinking) {
      if (gb.buttons.pressed(BUTTON_UP)) {
          linkAndMoveIfLegit(board, links, W, H, &cursor_x, &cursor_y, Direction::up_dir);
      }
      if (gb.buttons.pressed(BUTTON_RIGHT)) {
          linkAndMoveIfLegit(board, links, W, H, &cursor_x, &cursor_y, Direction::right_dir);
      }
      if (gb.buttons.pressed(BUTTON_DOWN)) {
          linkAndMoveIfLegit(board, links, W, H, &cursor_x, &cursor_y, Direction::down_dir);
      }
      if (gb.buttons.pressed(BUTTON_LEFT)) {
          linkAndMoveIfLegit(board, links, W, H, &cursor_x, &cursor_y, Direction::left_dir);
      }
    }


    if (gb.buttons.released(BUTTON_B)) {
        if (!ignoreRelease) {
            level = nextLevel(level);
            resetLevel();
        } else {
            ignoreRelease = false;
        }
    }

    if (gb.buttons.held(BUTTON_B, 25)) {
        ignoreRelease = true;
        resetLevel();
    }
}


