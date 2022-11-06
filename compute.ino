void compute() {
  updateDistributions(board, W, H, distributions, colorOrder, SCORE_SCALE);
  updateScore(board, W, H, score);
}


