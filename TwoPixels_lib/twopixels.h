//
// Created by edoua on 02/02/2020.
//

#ifndef TWO_PIXELS_H
#define TWO_PIXELS_H

enum class Color : uint16_t {
    white = 0xFFFF,
    gray = 0xACD0,
    darkgray = 0x5268,
    black = 0x0000,
    purple = 0x9008,
    pink = 0xCA30,
    red = 0xD8E4,
    orange = 0xFD42,
    brown = 0xCC68,
    beige = 0xFEB2,
    yellow = 0xF720,
    lightgreen = 0x8668,
    green = 0x044A,
    darkblue = 0x0210,
    blue = 0x4439,
    lightblue = 0x7DDF,
};

const Color ALPHA = Color::yellow;
const Color BETA = Color::blue;
const Color GAMMA = Color::red;
const Color DELTA = Color::purple;
const Color OMEGA = Color::green;

void nextBoard(Color **board, Color **newBoard, int h, int w);

void nextBoard(Color **board, Color **newBoard, int h, int w) {
    for (int i=0; i < h; i++) {
        for (int j = 0; j < w; ++j) {
            newBoard[i][j] = board[i][j];
        }
    }
}

#endif //TWO_PIXELS_H
