//
// Created by edoua on 02/02/2020.
//

#ifndef TWO_PIXELS_H
#define TWO_PIXELS_H

#ifndef _GAMEBUINO_META_GRAPHICS_H_
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
#endif //_GAMEBUINO_META_GRAPHICS_H_

const Color ALPHA = Color::yellow;
const Color BETA = Color::blue;
const Color GAMMA = Color::red;
const Color DELTA = Color::purple;
const Color OMEGA = Color::green;

enum Direction {
    left_dir, right_dir, up_dir, down_dir
};


bool isMoveOK(Color **board, int x, int y, Direction direction);

Color **createBoardAtLevel(int *w, int *h, int level) {
    *w = 2;
    *h = 3;

    Color **newBoard = new Color *[*w];
    for (int x = 0; x < *w; ++x) {
        newBoard[x] = new Color[*h];
        for (int y = 0; y < *h; ++y) {
            newBoard[x][y] = ALPHA;
        }
    }

    newBoard[0][2] = BETA;
    return newBoard;
}

bool isMoveOK(Color **board, int W, int H, int x, int y, Direction direction) {
    switch (direction) {
        case Direction::left_dir:
            return x > 0;
        case Direction::right_dir:
            return x < W-1;
        case Direction::up_dir:
            return y > 0;
        case Direction::down_dir:
            return y < H-1;
        default: return false;
    };
}

#endif //TWO_PIXELS_H
