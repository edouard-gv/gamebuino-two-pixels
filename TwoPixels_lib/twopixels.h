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
    left_dir, right_dir, up_dir, down_dir, none
};


bool isMoveOK(Color **board, int x, int y, Direction direction);

Color **createAlphaBoard(int w, int h);

Color **createBoardAtLevel(int *pW, int *pH, int level) {
    if (level == 1) {
        *pW = 2;
        *pH = 3;
        Color **newBoard = createAlphaBoard(*pW, *pH);
        newBoard[0][2] = BETA;
        return newBoard;
    }

    if (level == 2) {
        *pW = 3;
        *pH = 3;
        return createAlphaBoard(*pW, *pH);
    }

    if (level == 3) {
        *pW = 3;
        *pH = 3;

        Color **newBoard = createAlphaBoard(*pW, *pH);
        newBoard[1][1] = BETA;
        return newBoard;
    }

    return nullptr;
}

Color **createAlphaBoard(int w, int h) {
    auto **newBoard = new Color *[w];
    for (int x = 0; x < w; ++x) {
        newBoard[x] = new Color[h];
        for (int y = 0; y < h; ++y) {
            newBoard[x][y] = ALPHA;
        }
    }
    return newBoard;
}

bool moveIfLegit(Color **board, int w, int h, int *pX, int *pY, Direction direction) {
    switch (direction) {
        case Direction::left_dir:
            return ((*pX > 0) && ((*pX = *pX - 1) || true)); //same as below, don't know what's better
        case Direction::right_dir:
            if (*pX < w - 1) {
                *pX = *pX + 1;
                return true;
            } else return false;
        case Direction::up_dir:
            if (*pY > 0) {
                *pY = *pY - 1;
                return true;
            } else
                return false;
        case Direction::down_dir:
            if (*pY < h - 1) {
                *pY = *pY + 1;
                return true;
            } else
                return false;
        default:
            return false;
    };
}

Direction **createEmptyLinks(int w, int h) {
    auto **links = new Direction *[w];
    for (int x = 0; x < w; ++x) {
        links[x] = new Direction[h];
        for (int y = 0; y < h; ++y) {
            links[x][y] = Direction::none;
        }
    }
    return links;
}

bool linkAndMoveIfLegit(Color **board, Direction **links, int w, int h, int *pX, int *pY, Direction direction) {
    int pCopyX = *pX;
    int pCopyY = *pY;

    if (!moveIfLegit(board, w, h, &pCopyX, &pCopyY, direction)) {
        return false;
    }

    switch (direction) {
        case Direction::left_dir:
            if (board[*pX][*pY] == board[*pX - 1][*pY]) {
                links[*pX][*pY] = direction;
                *pX = *pX - 1;
                return true;
            } else
                return false;
        case Direction::right_dir:
            if (board[*pX][*pY] == board[*pX + 1][*pY]) {
                links[*pX][*pY] = direction;
                *pX = *pX + 1;
                return true;
            } else
                return false;
        case Direction::up_dir:
            if (board[*pX][*pY] == board[*pX][*pY - 1]) {
                links[*pX][*pY] = direction;
                *pY = *pY - 1;
                return true;
            } else
                return false;
        case Direction::down_dir:
            if (board[*pX][*pY] == board[*pX][*pY + 1]) {
                links[*pX][*pY] = direction;
                *pY = *pY + 1;
                return true;
            } else
                return false;
        default:
            return false;
    };
}

void resetLinks(Direction **links, int w, int h) {
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            links[x][y] = Direction::none;
        }
    }
}

void deleteBoard(Color **board, int W) {
    for (int x = 0; x < W; x++) {
        delete board[x];
    }
    delete board;
}

void deleteLinks(Direction **links, int W) {
    for (int x = 0; x < W; x++) {
        delete links[x];
    }
    delete links;
}

#endif //TWO_PIXELS_H
