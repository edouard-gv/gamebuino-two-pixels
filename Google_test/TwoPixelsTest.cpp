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

TEST(TwoPixelsTestSuite_levels, Initialize) {
    int W = 0;
    int H = 0;

    auto **expected = new Color *[2]{
            new Color[3]{ALPHA, ALPHA, BETA},
            new Color[3]{ALPHA, ALPHA, ALPHA}
    };

    Color **board = createBoardAtLevel(&W, &H, 1);

    EXPECT_EQ(2, W);
    EXPECT_EQ(3, H);

    assertExpectedBoard(expected, board, W, H);

    deleteBoard(board, W);
    deleteBoard(expected, W);
}

TEST(TwoPixelsTestSuite_levels, nextLevel) {
    EXPECT_EQ(2, nextLevel(1));
    EXPECT_EQ(countLevels(), nextLevel(countLevels() - 1));
    EXPECT_EQ(1, nextLevel(countLevels()));
}

TEST(TwoPixelsTestSuite_move, OKs) {
    int W = 0;
    int H = 0;

    Color **board = createBoardAtLevel(&W, &H, 1);

    int x = 1;
    int y = 0;
    EXPECT_TRUE(moveIfLegit(board, W, H, &x, &y, Direction::left_dir));
    EXPECT_EQ(0, x);
    EXPECT_EQ(0, y);
    EXPECT_TRUE(moveIfLegit(board, W, H, &x, &y, Direction::down_dir));
    EXPECT_EQ(0, x);
    EXPECT_EQ(1, y);
    EXPECT_TRUE(moveIfLegit(board, W, H, &x, &y, Direction::right_dir));
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_TRUE(moveIfLegit(board, W, H, &x, &y, Direction::up_dir));
    EXPECT_EQ(1, x);
    EXPECT_EQ(0, y);

    deleteBoard(board, W);
}

TEST(TwoPixelsTestSuite_move, KOs) {
    int W = 0;
    int H = 0;

    Color **board = createBoardAtLevel(&W, &H, 1);

    int x = 1;
    int y = 0;
    EXPECT_FALSE(moveIfLegit(board, W, H, &x, &y, Direction::right_dir));
    EXPECT_EQ(1, x);
    EXPECT_EQ(0, y);
    EXPECT_FALSE(moveIfLegit(board, W, H, &x, &y, Direction::up_dir));
    EXPECT_EQ(1, x);
    EXPECT_EQ(0, y);

    x = 0;
    y = 2;
    EXPECT_FALSE(moveIfLegit(board, W, H, &x, &y, Direction::left_dir));
    EXPECT_EQ(0, x);
    EXPECT_EQ(2, y);
    EXPECT_FALSE(moveIfLegit(board, W, H, &x, &y, Direction::down_dir));
    EXPECT_EQ(0, x);
    EXPECT_EQ(2, y);

    deleteBoard(board, W);
}

TEST(TwoPixelsTestSuite_links, Unitary) {
    int W = 0;
    int H = 0;

    Color **board = createBoardAtLevel(&W, &H, 2);
    Direction **links = createEmptyLinks(W, H);

    int x = 1;
    int y = 1;
    EXPECT_EQ(Direction::none, links[1][1]);
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::right_dir));
    EXPECT_EQ(Direction::right_dir, links[1][1]);
    EXPECT_EQ(2, x);
    EXPECT_EQ(1, y);
    EXPECT_EQ(Direction::end, links[2][1]);


    deleteBoard(board, W);
    deleteLinks(links, W);
}

TEST(TwoPixelsTestSuite_links, Walk) {
    int W = 0;
    int H = 0;

    Color **board = createBoardAtLevel(&W, &H, 2);
    Direction **links = createEmptyLinks(W, H);

    int x = 1;
    int y = 1;
    EXPECT_EQ(Direction::none, links[1][1]);
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::right_dir));
    EXPECT_EQ(Direction::right_dir, links[1][1]);
    EXPECT_EQ(2, x);
    EXPECT_EQ(1, y);
    EXPECT_EQ(Direction::end, links[2][1]);

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::up_dir));
    EXPECT_EQ(Direction::up_dir, links[2][1]);
    EXPECT_EQ(2, x);
    EXPECT_EQ(0, y);
    EXPECT_EQ(Direction::end, links[2][0]);

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::left_dir));
    EXPECT_EQ(Direction::left_dir, links[2][0]);
    EXPECT_EQ(1, x);
    EXPECT_EQ(0, y);
    EXPECT_EQ(Direction::end, links[1][0]);

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::left_dir));
    EXPECT_EQ(Direction::left_dir, links[1][0]);
    EXPECT_EQ(0, x);
    EXPECT_EQ(0, y);
    EXPECT_EQ(Direction::end, links[0][0]);

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::down_dir));
    EXPECT_EQ(Direction::down_dir, links[0][0]);
    EXPECT_EQ(0, x);
    EXPECT_EQ(1, y);
    EXPECT_EQ(Direction::end, links[0][1]);

    deleteBoard(board, W);
    deleteLinks(links, W);
}

TEST(TwoPixelsTestSuite_links, KOForColor) {
    int W = 0;
    int H = 0;

    Color **board = createBoardAtLevel(&W, &H, 3);
    Direction **links = createEmptyLinks(W, H);

    int x = 1;
    int y = 1;
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::right_dir));
    EXPECT_EQ(Direction::none, links[1][1]);
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::up_dir));
    EXPECT_EQ(Direction::none, links[1][1]);
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::left_dir));
    EXPECT_EQ(Direction::none, links[1][1]);
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::down_dir));
    EXPECT_EQ(Direction::none, links[1][1]);
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);

    deleteBoard(board, W);
    deleteLinks(links, W);

}

TEST(TwoPixelsTestSuite_links, KOForBorders) {
    int W = 0;
    int H = 0;

    Color **board = createBoardAtLevel(&W, &H, 3);
    Direction **links = createEmptyLinks(W, H);
    int x = 0;
    int y = 0;
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::left_dir));
    EXPECT_EQ(Direction::none, links[0][0]);

    deleteBoard(board, W);
    deleteLinks(links, W);

}

TEST(TwoPixelsTestSuite_links, resetLinks) {
    Direction **links = createEmptyLinks(2, 3);
    links[1][1] = Direction::right_dir;
    resetLinks(links, 2, 3);
    EXPECT_EQ(Direction::none, links[1][1]);
}


TEST(TwoPixelsTestSuite_links, RewindToPrevious) {
    int W = 0;
    int H = 0;

    Color **board = createBoardAtLevel(&W, &H, 2);
    Direction **links = createEmptyLinks(W, H);

    links[0][1] = Direction::right_dir;
    links[1][1] = Direction::right_dir;
    links[2][1] = Direction::end;
    int x = 2;
    int y = 1;
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::left_dir));
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_EQ(Direction::none, links[2][1]);
    EXPECT_EQ(Direction::end, links[1][1]);
}

TEST(TwoPixelsTestSuite_links, isAlone) {
    int W = 3;
    int H = 4;

    Direction **links = createEmptyLinks(W, H);

    EXPECT_TRUE(isAlone(links, W, H, 1, 1));
    EXPECT_TRUE(isAlone(links, W, H, 0, H-1));
    EXPECT_TRUE(isAlone(links, W, H, W-1, 0));
}

TEST(TwoPixelsTestSuite_links, isNotAlone) {
    int W = 3;
    int H = 4;

    Direction **links = createEmptyLinks(W, H);

    links[1][1] = Direction::left_dir;
    links[1][2] = Direction::left_dir;

    //EXPECT_FALSE(isAlone(links, W, H, 1, 1));
    EXPECT_FALSE(isAlone(links, W, H, 0, H-1));
    EXPECT_FALSE(isAlone(links, W, H, W-1, 0));
}

TEST(TwoPixelsTestSuite_links, RewindToNone) {
    int W = 0;
    int H = 0;

    Color **board = createBoardAtLevel(&W, &H, 2);
    Direction **links = createEmptyLinks(W, H);

    links[1][1] = Direction::right_dir;
    links[2][1] = Direction::end;
    int x = 2;
    int y = 1;
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::left_dir));
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_EQ(Direction::none, links[2][1]);
    EXPECT_EQ(Direction::none, links[1][1]);

    links[1][1] = Direction::left_dir;
    links[0][1] = Direction::end;
    x = 0;
    y = 1;
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::right_dir));
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_EQ(Direction::none, links[0][1]);
    EXPECT_EQ(Direction::none, links[1][1]);

    links[1][1] = Direction::up_dir;
    links[1][0] = Direction::end;
    x = 1;
    y = 0;
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::down_dir));
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_EQ(Direction::none, links[1][0]);
    EXPECT_EQ(Direction::none, links[1][1]);

    links[1][1] = Direction::down_dir;
    links[1][2] = Direction::end;
    x = 1;
    y = 2;
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::up_dir));
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_EQ(Direction::none, links[1][0]);
    EXPECT_EQ(Direction::none, links[1][1]);

    deleteBoard(board, W);
    deleteLinks(links, W);
}

TEST(TwoPixelsTestSuite_cycle, square) {
    int W = 0;
    int H = 0;

    Color **board = createBoardAtLevel(&W, &H, 2);
    Direction **links = createEmptyLinks(W, H);

    links[1][1] = Direction::left_dir;
    links[0][1] = Direction::down_dir;
    links[0][2] = Direction::right_dir;
    int x = 1;
    int y = 2;

    EXPECT_EQ(Direction::none, links[1][2]);
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::up_dir));

    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::up_dir));
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::left_dir));
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::right_dir));

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::down_dir));
    EXPECT_EQ(Direction::left_dir, links[1][1]);
    EXPECT_EQ(Direction::none, links[1][2]);

}

TEST(TwoPixelsTestSuite_cycle, locking) {
    Direction **links = createEmptyLinks(1, 1);
    links[0][0] = Direction::right_dir;
    lockLinksAt(links, 0, 0);
    EXPECT_EQ(Direction::right_lock, links[0][0]);

    links[0][0] = Direction::left_dir;
    lockLinksAt(links, 0, 0);
    EXPECT_EQ(Direction::left_lock, links[0][0]);

    links[0][0] = Direction::up_dir;
    lockLinksAt(links, 0, 0);
    EXPECT_EQ(Direction::up_lock, links[0][0]);

    links[0][0] = Direction::down_dir;
    lockLinksAt(links, 0, 0);
    EXPECT_EQ(Direction::down_lock, links[0][0]);
}

TEST(TwoPixelsTestSuite_cycle, unlocking) {
    Direction **links = createEmptyLinks(1, 1);
    links[0][0] = Direction::right_lock;
    unlockLinksAt(links, 0, 0);
    EXPECT_EQ(Direction::right_dir, links[0][0]);

    links[0][0] = Direction::left_lock;
    unlockLinksAt(links, 0, 0);
    EXPECT_EQ(Direction::left_dir, links[0][0]);

    links[0][0] = Direction::up_lock;
    unlockLinksAt(links, 0, 0);
    EXPECT_EQ(Direction::up_dir, links[0][0]);

    links[0][0] = Direction::down_lock;
    unlockLinksAt(links, 0, 0);
    EXPECT_EQ(Direction::down_dir, links[0][0]);
}

TEST(TwoPixelsTestSuite_cycle, isLocked) {
    EXPECT_TRUE(isLocked(Direction::down_lock));
    EXPECT_TRUE(isLocked(Direction::up_lock));
    EXPECT_TRUE(isLocked(Direction::left_lock));
    EXPECT_TRUE(isLocked(Direction::right_lock));
    EXPECT_FALSE(isLocked(Direction::down_dir));
    EXPECT_FALSE(isLocked(Direction::up_dir));
    EXPECT_FALSE(isLocked(Direction::left_dir));
    EXPECT_FALSE(isLocked(Direction::right_dir));
}

TEST(TwoPixelsTestSuite_consume, OK) {
    int W = 0;
    int H = 0;

    Color **board = createBoardAtLevel(&W, &H, 4);
    Direction **links = createEmptyLinks(W, H);


    int x = 0;
    int y = 2;
    linkAndMoveIfLegit(board, links, W, H, &x, &y, Direction::right_dir);

    consumeLinks(board, links, W, H);

    EXPECT_EQ(OMEGA, board[0][0]);
    EXPECT_EQ(OMEGA, board[1][0]);
    EXPECT_EQ(ALPHA, board[0][1]);
    EXPECT_EQ(BETA, board[1][1]);
    EXPECT_EQ(GAMMA, board[0][2]);
    EXPECT_EQ(DELTA, board[1][2]);
}


TEST(TwoPixelsTestSuite_shiftDown, trivial) {
    int W = 0;
    int H = 0;

    Color **board = createBoardAtLevel(&W, &H, 4);

    shiftDown(board, 0, 0);

    EXPECT_EQ(OMEGA, board[0][0]);
}

TEST(TwoPixelsTestSuite_shiftDown, oneFloor) {
    int W = 0;
    int H = 0;

    Color **board = createBoardAtLevel(&W, &H, 4);
    EXPECT_EQ(BETA, board[1][0]);

    shiftDown(board, 1, 1);

    EXPECT_EQ(OMEGA, board[1][0]);
    EXPECT_EQ(BETA, board[1][1]);
}

TEST(TwoPixelsTestSuite_shiftDown, twoFloors) {
    int W = 0;
    int H = 0;

    Color **board = createBoardAtLevel(&W, &H, 4);
    EXPECT_EQ(BETA, board[1][0]);
    EXPECT_EQ(DELTA, board[1][1]);

    shiftDown(board, 1, 2);

    EXPECT_EQ(OMEGA, board[1][0]);
    EXPECT_EQ(BETA, board[1][1]);
    EXPECT_EQ(DELTA, board[1][2]);
}

TEST(TwoPixelsTestSuite, sandbox) {
    EXPECT_EQ(-1 % 4, -1);
}