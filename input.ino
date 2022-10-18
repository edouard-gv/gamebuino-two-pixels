void input() {

    if (gb.buttons.held(BUTTON_A, 0)) {
      isLinking = true;
    }

    if (gb.buttons.released(BUTTON_A)) {
      isLinking = false;
      links = createEmptyLinks(W, H); //TODO Empty it instead of create a new one;
    }

    if (!isLinking) {
      if (gb.buttons.pressed(BUTTON_UP)) {
          if (isMoveOK(board, W, H, cursor_x, cursor_y, Direction::up_dir))
              cursor_y--;
      }
      if (gb.buttons.pressed(BUTTON_RIGHT)) {
          if (isMoveOK(board, W, H, cursor_x, cursor_y, Direction::right_dir))
              cursor_x++;
      }
      if (gb.buttons.pressed(BUTTON_DOWN)) {
          if (isMoveOK(board, W, H, cursor_x, cursor_y, Direction::down_dir))
              cursor_y++;
      }
      if (gb.buttons.pressed(BUTTON_LEFT)) {
          if (isMoveOK(board, W, H, cursor_x, cursor_y, Direction::left_dir))
              cursor_x--;
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
            board = createBoardAtLevel(&W, &H, level++); //TODO delete before
            links = createEmptyLinks(W, H); //TODO delete before
        } else {
            ignoreRelease = false;
        }
    }

    if (gb.buttons.held(BUTTON_B, 25)) {
        ignoreRelease = true;
        level = 1;
        board = createBoardAtLevel(&W, &H, level); //TODO delete before
        links = createEmptyLinks(W, H); //TODO delete before
    }
}


