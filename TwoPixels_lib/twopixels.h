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

#define min(a, b) ((a)<(b)?(a):(b))
#define max(a, b) ((a)>(b)?(a):(b))

#endif //_GAMEBUINO_META_GRAPHICS_H_

const Color ALPHA = Color::yellow;
const Color BETA = Color::blue;
const Color GAMMA = Color::red;
const Color DELTA = Color::purple;
const Color OMEGA = Color::green;

enum Direction {
    left_dir, right_dir, up_dir, down_dir, none, end,
    left_lock, right_lock, up_lock, down_lock
};

Color randomColor() {

    switch (rand() % 5) {
        case 0:
            return ALPHA;
        case 1:
            return BETA;
        case 2:
            return GAMMA;
        case 3:
            return DELTA;
        case 4:
            return OMEGA;
    }
    return OMEGA;
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

int countLevels() {
    return 5;
}

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

    if (level == 4) {
        *pW = 2;
        *pH = 3;

        Color **newBoard = createAlphaBoard(*pW, *pH);
        newBoard[0][0] = ALPHA;
        newBoard[1][0] = BETA;
        newBoard[0][1] = GAMMA;
        newBoard[1][1] = DELTA;
        return newBoard;
    }

    if (level == 5) {
        *pW = 8;
        *pH = 6;

        auto **newBoard = new Color *[*pW];
        for (int x = 0; x < *pW; ++x) {
            newBoard[x] = new Color[*pH];
            for (int y = 0; y < *pH; ++y) {
                newBoard[x][y] = randomColor();
            }
        }
        return newBoard;
    }

    return nullptr;
}

int nextLevel(int level) {
    return (level % countLevels()) + 1;
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

int estimateNextX(int x, Direction direction) {
    switch (direction) {
        case Direction::left_dir:
            return x - 1;
        case Direction::right_dir:
            return x + 1;
        default:
            return x;
    }
}

int estimateNextY(int y, Direction direction) {
    switch (direction) {
        case Direction::up_dir:
            return y - 1;
        case Direction::down_dir:
            return y + 1;
        default:
            return y;
    }
}

bool isMoveLegit(int w, int h, int x, int y, Direction direction) {
    return ((direction == left_dir) && (x > 0)) ||
           ((direction == right_dir) && (x < w - 1)) ||
           ((direction == up_dir) && (y > 0)) ||
           ((direction == down_dir) && (y < h - 1));
}

bool moveIfLegit(Color **board, int w, int h, int *pX, int *pY, Direction direction) {
    int nextX = estimateNextX(*pX, direction);
    int nextY = estimateNextY(*pY, direction);

    if (isMoveLegit(w, h, *pX, *pY, direction)) {
        *pX = nextX;
        *pY = nextY;
        return true;
    }
    return false;
}

Direction opposite(Direction direction) {
    switch (direction) {
        case Direction::left_dir:
            return Direction::right_dir;
        case Direction::right_dir:
            return Direction::left_dir;
        case Direction::up_dir:
            return Direction::down_dir;
        case Direction::down_dir:
            return Direction::up_dir;
        default:
            return direction;
    }
}

Direction toggleLock(Direction direction) {
    switch (direction) {
        case Direction::left_dir:
            return Direction::left_lock;
        case Direction::right_dir:
            return Direction::right_lock;
        case Direction::up_dir:
            return Direction::up_lock;
        case Direction::down_dir:
            return Direction::down_lock;
        case Direction::left_lock:
            return Direction::left_dir;
        case Direction::right_lock:
            return Direction::right_dir;
        case Direction::up_lock:
            return Direction::up_dir;
        case Direction::down_lock:
            return Direction::down_dir;
        default:
            return direction;
    }
}

void lockLinksAt(Direction **links, int x, int y) {
    links[x][y] = toggleLock(links[x][y]);
}

void unlockLinksAt(Direction **links, int x, int y) {
    links[x][y] = toggleLock(links[x][y]);
}

bool isLocked(Direction direction) {
    return (direction == Direction::down_lock ||
            direction == Direction::up_lock ||
            direction == Direction::left_lock ||
            direction == Direction::right_lock);
}

bool isAlone(Direction **links, int w, int h, int x, int y) {
    int minX = max(0, x - 1);
    int maxX = min(w - 1, x + 1);
    int minY = max(0, y - 1);
    int maxY = min(h - 1, y + 1);
    for (int i = minX; i <= maxX; ++i) {
        for (int j = minY; j <= maxY; ++j) {
            if (!(i == x && j == y) && (links[i][j] != Direction::none)) {
                return false;
            }
        }
    }
    return true;
}

bool linkAndMoveIfLegit(Color **board, Direction **links, int w, int h, int *pX, int *pY, Direction direction) {
    if (!isMoveLegit(w, h, *pX, *pY, direction)) {
        return false;
    }

    int nextX = estimateNextX(*pX, direction);
    int nextY = estimateNextY(*pY, direction);

    if (!isLocked(links[*pX][*pY])) {
        if (board[*pX][*pY] == board[nextX][nextY]) {
            if (links[nextX][nextY] == opposite(direction)) { //rewind
                links[*pX][*pY] = Direction::none;
                if (!isAlone(links, w, h, nextX, nextY)) {
                    links[nextX][nextY] = Direction::end;
                } else {
                    links[nextX][nextY] = Direction::none;
                }
            } else {
                links[*pX][*pY] = direction;
                if (links[nextX][nextY] != Direction::none) {
                    lockLinksAt(links, nextX, nextY);
                } else {
                    links[nextX][nextY] = Direction::end;
                }
            }
            *pX = nextX;
            *pY = nextY;
            return true;
        } else {
            return false;
        }
    }
    //we are locked
    if (links[nextX][nextY] == opposite(direction)) {
        unlockLinksAt(links, *pX, *pY);
        links[nextX][nextY] = Direction::none;
        *pX = nextX;
        *pY = nextY;
        return true;
    }
    return false;
}

void shiftDown(Color **board, int x, int y) {
    for (int j = y; j > 0; j--) {
        board[x][j] = board[x][j - 1];
    }
    board[x][0] = randomColor();
}

void consumeLinks(Color **board, Direction **links, int W, int H) {
    for (int x = 0; x < W; x++)
        for (int y = 0; y < H; y++) {
            if (links[x][y] != Direction::none) {
                shiftDown(board, x, y);
            }
        };
}

#endif //TWO_PIXELS_H
