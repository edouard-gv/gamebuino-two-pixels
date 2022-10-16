void input() {
  int H = gb.display.height();
  int W = gb.display.width();

  if (gb.buttons.repeat(BUTTON_A, 0)) {
    nextWorld(world, newWorld, H, W);
    bool **tmp = world;
    world = newWorld;
    newWorld = tmp;
  }

  if (gb.buttons.held(BUTTON_B, 25)) {
    initializeWorld(world, H, W);
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


