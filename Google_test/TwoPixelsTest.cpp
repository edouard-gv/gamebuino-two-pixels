#include "gtest/gtest.h"
#include "twopixels.h"

std::string print_color(Color color) {
    switch (color) {
        case ALPHA  :
            return "a";
        case BETA  :
            return "b";
        case GAMMA  :
            return "c";
        case DELTA  :
            return "d";
        case OMEGA  :
            return "z";
        default:
            return "?";
    }
}

Color **createEmptyBoard(int W, int H) {
    Color **newBoard = new Color *[W];
    for (int x = 0; x < W; ++x) {
        newBoard[x] = new Color[H];
    }
    return newBoard;
}

void deleteBoard(Color **board, int W) {
    for (int x = 0; x < W; x++) {
        delete board[x];
    }
    delete board;
}

std::string scoord(int x, int y) { return std::to_string(x) + "," + std::to_string(y) + ": "; }

void assertExpectedBoard(Color **expected, Color **board, int W, int H) {
    for (int x = 0; x < W; x++) {
        for (int y = 0; y < H; y++) {
            std::string board_v = scoord(x, y) + print_color(board[x][y]);
            std::string expected_v = scoord(x, y) + print_color(expected[x][y]);
            EXPECT_EQ(board_v, expected_v);
        }
    }
}

TEST(TwoPixelsTestSuite, InitializeFirstLevel) {
    int W = 0;
    int H = 0;

    Color **expected = new Color *[2]{
            new Color[3]{ALPHA, ALPHA, BETA},
            new Color[3]{ALPHA, ALPHA, ALPHA}
    };

    Color **newBoard = createBoardAtLevel(&W, &H, 1);

    EXPECT_EQ(2, W);
    EXPECT_EQ(3, H);

    assertExpectedBoard(expected, newBoard, W, H);

    deleteBoard(newBoard, W);
    deleteBoard(expected, W);
}

TEST(TwoPixelsTestSuite, moveOKs) {
    int W = 0;
    int H = 0;

    Color **newBoard = createBoardAtLevel(&W, &H, 1);

    EXPECT_TRUE(isMoveOK(newBoard, W, H, 1, 0, Direction::left_dir));
    EXPECT_TRUE(isMoveOK(newBoard, W, H, 1, 0, Direction::down_dir));
    EXPECT_TRUE(isMoveOK(newBoard, W, H, 0, 1, Direction::right_dir));
    EXPECT_TRUE(isMoveOK(newBoard, W, H, 0, 1, Direction::up_dir));

    deleteBoard(newBoard, W);
}

TEST(TwoPixelsTestSuite, moveKOs) {
    int H = 0;
    int W = 0;

    Color **newBoard = createBoardAtLevel(&W, &H, 1);

    EXPECT_FALSE(isMoveOK(newBoard, W, H, 1, 0, Direction::right_dir));
    EXPECT_FALSE(isMoveOK(newBoard, W, H, 1, 0, Direction::up_dir));
    EXPECT_FALSE(isMoveOK(newBoard, W, H, 0, 2, Direction::left_dir));
    EXPECT_FALSE(isMoveOK(newBoard, W, H, 0, 2, Direction::down_dir));

    deleteBoard(newBoard, W);
}


TEST(TwoPixelsTestSuite, sandbox) {
    EXPECT_EQ(-1 % 4, -1);
}