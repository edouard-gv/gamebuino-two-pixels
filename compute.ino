void compute() {
  if (hasChanged) {
    updateDistributions(board, W, H, distributions, colorOrder, SCORE_SCALE);
    updateScore(board, W, H, score);
    save();
    hasChanged = false;
  }
}


