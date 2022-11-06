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

const int THRESHOLD_MEDIUM = 50;
const int THRESHOLD_HIGH = 80;
const int THRESHOLD_LOW = 5;

const Color ALPHA = Color::yellow;
const Color BETA = Color::blue;
const Color GAMMA = Color::red;
const Color DELTA = Color::purple;
const Color OMEGA = Color::green;

const Color all_colors[] = {ALPHA, BETA, GAMMA, DELTA, OMEGA};

const int COLOR_COUNT = 5;

enum Command {
    left_cmd, right_cmd, up_cmd, down_cmd
};

enum Direction {
    left_dir, right_dir, up_dir, down_dir, none, end,
    left_lock, right_lock, up_lock, down_lock
};

Direction map(Command command) {
    switch (command) {
        case Command::left_cmd:
            return Direction::left_dir;
        case Command::right_cmd:
            return Direction::right_dir;
        case Command::up_cmd:
            return Direction::up_dir;
        case Command::down_cmd:
            return Direction::down_dir;
        default:
            return Direction::none;
    }
}

Command map(Direction direction) {
    switch (direction) {
        case Direction::left_dir:
            return Command::left_cmd;
        case Direction::right_dir:
            return Command::right_cmd;
        case Direction::up_dir:
            return Command::up_cmd;
        case Direction::left_lock:
            return Command::left_cmd;
        case Direction::right_lock:
            return Command::right_cmd;
        case Direction::up_lock:
            return Command::up_cmd;
        default:
            return Command::down_cmd;
    }
}


Color randomColor() {
    return all_colors[rand() % 5];
}

int indexOf(Color color) {
    switch (color) {
        case ALPHA:
            return 0;
        case BETA:
            return 1;
        case GAMMA:
            return 2;
        case DELTA:
            return 3;
        default :
            return 4; //OMEGA
    }
}

int countLevels() {
    return 2;
}

int nextLevel(int level) {
    return (level % countLevels()) + 1;
}

Color **createBoardAtLevel(int *pW, int *pH, int level) {
    *pW = 9;
    *pH = 7;

    auto **newBoard = new Color *[*pW];
    for (int x = 0; x < *pW; ++x) {
        newBoard[x] = new Color[*pH];
        for (int y = 0; y < *pH; ++y) {
            newBoard[x][y] = randomColor();
        }
    }
    return newBoard;
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

int estimateNextX(int x, Command command) {
    switch (command) {
        case Command::left_cmd:
            return x - 1;
        case Command::right_cmd:
            return x + 1;
        default:
            return x;
    }
}

int estimateNextY(int y, Command command) {
    switch (command) {
        case Command::up_cmd:
            return y - 1;
        case Command::down_cmd:
            return y + 1;
        default:
            return y;
    }
}

bool isMoveLegit(int w, int h, int x, int y, Command command) {
    return ((command == left_cmd) && (x > 0)) ||
           ((command == right_cmd) && (x < w - 1)) ||
           ((command == up_cmd) && (y > 0)) ||
           ((command == down_cmd) && (y < h - 1));
}

bool moveIfLegit(Color **board, int w, int h, int *pX, int *pY, Command command) {
    int nextX = estimateNextX(*pX, command);
    int nextY = estimateNextY(*pY, command);

    if (isMoveLegit(w, h, *pX, *pY, command)) {
        *pX = nextX;
        *pY = nextY;
        return true;
    }
    return false;
}

Command opposite(Command command) {
    switch (command) {
        case Command::left_cmd:
            return Command::right_cmd;
        case Command::right_cmd:
            return Command::left_cmd;
        case Command::up_cmd:
            return Command::down_cmd;
        default: //case Command::down_cmd:
            return Command::up_cmd;
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

bool linkAndMoveIfLegit(Color **board, Direction **links, int w, int h, int *pX, int *pY, Command command) {
    if (!isMoveLegit(w, h, *pX, *pY, command)) {
        return false;
    }

    int nextX = estimateNextX(*pX, command);
    int nextY = estimateNextY(*pY, command);

    if (!isLocked(links[*pX][*pY])) {
        if (board[*pX][*pY] == board[nextX][nextY]) {
            if (links[nextX][nextY] == map(opposite(command))) { //rewind
                links[*pX][*pY] = Direction::none;
                if (!isAlone(links, w, h, nextX, nextY)) {
                    links[nextX][nextY] = Direction::end;
                } else {
                    links[nextX][nextY] = Direction::none;
                }
            } else {
                links[*pX][*pY] = map(command);
                if (links[nextX][nextY] != Direction::none) {
                    lockLinksAt(links, nextX, nextY);
                    lockLinksAt(links, *pX, *pY);
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
    if (links[nextX][nextY] == toggleLock(map(opposite(command)))) {
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

bool consumeLinks(Color **board, Direction **links, int W, int H) {
    bool something_happened = false;
    for (int x = 0; x < W; x++)
        for (int y = 0; y < H; y++) {
            if (links[x][y] != Direction::none) {
                something_happened = true;
                shiftDown(board, x, y);
            }
        };
    return something_happened;
}

int countPositionsIShouldShiftDown(Direction **links, int W, int H, int x, int y) {
    int nbHolesInColumn = 0;
    bool hasHolesBelowMe = false;
    for (int j = 0; j < H; ++j) {
        if (links[x][j] != Direction::none) {
            nbHolesInColumn++;
            if (j >= y) {
                hasHolesBelowMe = true;
            }
        }
    }
    return (hasHolesBelowMe ? nbHolesInColumn : 0);
}

struct DistributionElement {
    int count;
    Color color;

    bool isSmallerThan(DistributionElement d) {
        if (this->count < d.count) {
            return true;
        } else if (this->count == d.count && indexOf(this->color) <= indexOf(d.color)) {
            return true;
        }
        return false;
    }
};

void countColors(Color *const *board, int W, int H, int *counts);

void sortDistributionElements(DistributionElement *elements) {
    for (int k = COLOR_COUNT - 1; k >= 1; --k) {
        for (int l = 0; l < k; ++l) {
            if (elements[l + 1].isSmallerThan(elements[l])) {
                DistributionElement tmpElement = elements[l + 1];
                elements[l + 1] = elements[l];
                elements[l] = tmpElement;
            }
        }
    }

}

void updateDistributions(Color **board, int W, int H, int *distributions, Color *colorOrder, int scale) {
    int counts[COLOR_COUNT];
    DistributionElement distributionElements[5];

    countColors(board, W, H, counts);

    for (int k = 0; k < COLOR_COUNT; ++k) {
        DistributionElement element;
        element.count = counts[k];
        element.color = all_colors[k];
        distributionElements[k] = element;
    }

    sortDistributionElements(distributionElements);

    for (int k = 0; k < COLOR_COUNT; ++k) {
        distributions[k] = round(distributionElements[k].count / (float) (W * H) * scale);
        colorOrder[k] = distributionElements[k].color;
    }
}

void updateScore(Color **board, int W, int H, bool *score) {
    int counts[COLOR_COUNT];
    countColors(board, W, H, counts);

    for (int k = 0; k < COLOR_COUNT; ++k) {
        if (counts[k]*100 <= THRESHOLD_LOW*(W*H)) {
            score[k*3] = true;
        }
    }
    for (int k = 0; k < COLOR_COUNT; ++k) {
        if (counts[k]*100 >= THRESHOLD_MEDIUM * (W * H)) {
            score[k*3+1] = true;
        }
    }
    for (int k = 0; k < COLOR_COUNT; ++k) {
        if (counts[k]*100 >= THRESHOLD_HIGH*(W*H)) {
            score[k*3+2] = true;
        }
    }
}

void countColors(Color *const *board, int W, int H, int *counts) {
    for (int k = 0; k < COLOR_COUNT; ++k) {
        counts[k] = 0;
    }
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            switch (board[i][j]) {
                case ALPHA:
                    counts[0]++;
                    break;
                case BETA:
                    counts[1]++;
                    break;
                case GAMMA:
                    counts[2]++;
                    break;
                case DELTA:
                    counts[3]++;
                    break;
                case OMEGA:
                    counts[4]++;
                    break;
            }
        }
    }
}

#endif //TWO_PIXELS_H
