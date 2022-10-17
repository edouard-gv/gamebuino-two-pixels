void input() {

  if (gb.buttons.repeat(BUTTON_A, 0)) {
  }

  if (gb.buttons.held(BUTTON_B, 25)) {
    //DO something
    ignoreRelease = true;
  }

  if (gb.buttons.released(BUTTON_B)) {
    if (!ignoreRelease) {
      //DO something else
    }
    else {
      ignoreRelease = false;
    }
  }
}


