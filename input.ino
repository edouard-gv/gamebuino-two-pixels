void input() {

    if (gb.buttons.held(BUTTON_A, 0)) {
      isLinking = true;
    }

    if (gb.buttons.released(BUTTON_A)) {
      isLinking = false;
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
            deleteBoard(board, W);
            deleteLinks(links, W);
            board = createBoardAtLevel(&W, &H, level++);
            links = createEmptyLinks(W, H);
        } else {
            ignoreRelease = false;
        }
    }

    if (gb.buttons.held(BUTTON_B, 25)) {
        ignoreRelease = true;
        level = 1;
        deleteBoard(board, W);
        deleteLinks(links, W);
        board = createBoardAtLevel(&W, &H, level);
        links = createEmptyLinks(W, H);
    }
}


