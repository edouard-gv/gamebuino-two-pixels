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
      isDrifting = consumeLinks(board, links, W, H);
    }

    if (!isLinking) {
      if (gb.buttons.pressed(BUTTON_UP)) {
          moveIfLegit(board, W, H, &cursor_x, &cursor_y, Command::up_cmd);
      }
      if (gb.buttons.pressed(BUTTON_RIGHT)) {
          moveIfLegit(board, W, H, &cursor_x, &cursor_y, Command::right_cmd);
      }
      if (gb.buttons.pressed(BUTTON_DOWN)) {
          moveIfLegit(board, W, H, &cursor_x, &cursor_y, Command::down_cmd);
      }
      if (gb.buttons.pressed(BUTTON_LEFT)) {
          moveIfLegit(board, W, H, &cursor_x, &cursor_y, Command::left_cmd);
      }
    }

    if (isLinking) {
      if (gb.buttons.pressed(BUTTON_UP)) {
          linkAndMoveIfLegit(board, links, W, H, &cursor_x, &cursor_y, Command::up_cmd);
      }
      if (gb.buttons.pressed(BUTTON_RIGHT)) {
          linkAndMoveIfLegit(board, links, W, H, &cursor_x, &cursor_y, Command::right_cmd);
      }
      if (gb.buttons.pressed(BUTTON_DOWN)) {
          linkAndMoveIfLegit(board, links, W, H, &cursor_x, &cursor_y, Command::down_cmd);
      }
      if (gb.buttons.pressed(BUTTON_LEFT)) {
          linkAndMoveIfLegit(board, links, W, H, &cursor_x, &cursor_y, Command::left_cmd);
      }
    }


    if (gb.buttons.released(BUTTON_B)) {
        if (!ignoreRelease) {
            level = nextLevel(level);
            resetLevel();
            resetScore(score);
        } else {
            ignoreRelease = false;
        }
    }

    if (gb.buttons.held(BUTTON_B, 25)) {
        ignoreRelease = true;
        resetLevel();
        resetScore(score);
    }
}


