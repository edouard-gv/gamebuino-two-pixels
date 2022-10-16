#include "gtest/gtest.h"
#include "twopixels.h"

std::string print_color(Color color) {
    switch(color)
    {
        case ALPHA  : return "a";
        case BETA  : return "b";
        case GAMMA  : return "c";
        case DELTA  : return "d";
        case OMEGA  : return "z";
        default: return "?";
    }
}

void printfWorld(bool **world, int h, int w) {
    printf("\n");
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            printf("%i-", world[i][j]);
        }
        printf("\n");
    }
}


Color **createEmptyBoard(int h, int w) {
    Color **newBoard = new Color *[h];
    for (int i = 0; i < h; ++i) {
        newBoard[i] = new Color[w];
    }
    return newBoard;
}

void deleteBoard(Color **board, int h) {
    for (int i = 0; i < h; i++) {
        delete board[i];
    }
    delete board;
}

std::string scoord(int i, int j) { return std::to_string(i) + "," + std::to_string(j) + ": "; }

void assertExpectedBoard(Color **expected, Color **board, int h, int w) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            std::string board_v = scoord(i, j) + print_color(board[i][j]);
            std::string expected_v = scoord(i, j) + print_color(expected[i][j]);
            EXPECT_EQ(board_v, expected_v);
        }
    }
}

TEST(TwoPixelsTestSuite, Donothing) {
    int H = 3;
    int W = 2;

    Color **board = new Color *[H]{
            new Color[W]{ALPHA, ALPHA},
            new Color[W]{ALPHA, ALPHA},
            new Color[W]{ALPHA, ALPHA}
    };

    Color **expected = new Color *[H]{
            new Color[W]{ALPHA, ALPHA},
            new Color[W]{ALPHA, ALPHA},
            new Color[W]{ALPHA, ALPHA}
    };

    Color **newBoard = createEmptyBoard(H, W);
    nextBoard(board, newBoard,  H, W);
    assertExpectedBoard(expected, newBoard, H, W);

    deleteBoard(board, H);
    deleteBoard(newBoard, H);
    deleteBoard(expected, H);
}


TEST(TwoPixelsTestSuite, sandbox) {
    EXPECT_EQ(-1 % 4, -1);
}