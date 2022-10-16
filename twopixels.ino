#include <Gamebuino-Meta.h>
#include "TwoPixels_lib/twopixels.h"
bool **world;
bool **newWorld;
bool **savedWorld;

bool red;
bool ignoreRelease;

void setup() {
  gb.begin();

  red = true;
  ignoreRelease = false;
  const int height = gb.display.height();
  const int width = gb.display.width();

  world = new bool*[height];
  newWorld = new bool*[height];
  //savedWorld = new bool*[height];

  for (int i=0; i < height; i++) {
    world[i] = new bool[width];
    newWorld[i] = new bool[width];
    //savedWorld[i] = new bool[width];
  }

  initializeWorld(world, height, width);

  //copyWorld(world, savedWorld, height, width);

  //TODO: This must be put somewhere!
  /*
  for (int i = 0; i < HEIGHT; i++) {
    delete world[i];
    delete newWorld[i];
  }
  delete world;
  delete newWorld;
  delete savedWorld;
  */
}

void loop() {
  while(!gb.update());

  input();
  compute();
  render();
}

