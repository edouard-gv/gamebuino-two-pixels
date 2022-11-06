#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "twopixels.h"

using ::testing::ElementsAre;

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

Color **createTestBoard(int *pW, int *pH, int inputNumber) {
    if (inputNumber == 1) {
        *pW = 2;
        *pH = 3;
        Color **newBoard = createAlphaBoard(*pW, *pH);
        newBoard[0][2] = BETA;
        return newBoard;
    }

    if (inputNumber == 2) {
        *pW = 3;
        *pH = 3;
        return createAlphaBoard(*pW, *pH);
    }

    if (inputNumber == 3) {
        *pW = 3;
        *pH = 3;

        Color **newBoard = createAlphaBoard(*pW, *pH);
        newBoard[1][1] = BETA;
        return newBoard;
    }

    if (inputNumber == 4) {
        *pW = 2;
        *pH = 3;

        Color **newBoard = createAlphaBoard(*pW, *pH);
        newBoard[0][0] = ALPHA;
        newBoard[1][0] = BETA;
        newBoard[0][1] = GAMMA;
        newBoard[1][1] = DELTA;
        return newBoard;
    }

    if (inputNumber == 5) {
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

TEST(TwoPixelsTestSuite_levels, Initialize) {
    int W = 0;
    int H = 0;

    auto **expected = new Color *[2]{
            new Color[3]{ALPHA, ALPHA, BETA},
            new Color[3]{ALPHA, ALPHA, ALPHA}
    };

    Color **board = createTestBoard(&W, &H, 1);

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

    Color **board = createTestBoard(&W, &H, 1);

    int x = 1;
    int y = 0;
    EXPECT_TRUE(moveIfLegit(board, W, H, &x, &y, Command::left_cmd));
    EXPECT_EQ(0, x);
    EXPECT_EQ(0, y);
    EXPECT_TRUE(moveIfLegit(board, W, H, &x, &y, Command::down_cmd));
    EXPECT_EQ(0, x);
    EXPECT_EQ(1, y);
    EXPECT_TRUE(moveIfLegit(board, W, H, &x, &y, Command::right_cmd));
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_TRUE(moveIfLegit(board, W, H, &x, &y, Command::up_cmd));
    EXPECT_EQ(1, x);
    EXPECT_EQ(0, y);

    deleteBoard(board, W);
}

TEST(TwoPixelsTestSuite_move, KOs) {
    int W = 0;
    int H = 0;

    Color **board = createTestBoard(&W, &H, 1);

    int x = 1;
    int y = 0;
    EXPECT_FALSE(moveIfLegit(board, W, H, &x, &y, Command::right_cmd));
    EXPECT_EQ(1, x);
    EXPECT_EQ(0, y);
    EXPECT_FALSE(moveIfLegit(board, W, H, &x, &y, Command::up_cmd));
    EXPECT_EQ(1, x);
    EXPECT_EQ(0, y);

    x = 0;
    y = 2;
    EXPECT_FALSE(moveIfLegit(board, W, H, &x, &y, Command::left_cmd));
    EXPECT_EQ(0, x);
    EXPECT_EQ(2, y);
    EXPECT_FALSE(moveIfLegit(board, W, H, &x, &y, Command::down_cmd));
    EXPECT_EQ(0, x);
    EXPECT_EQ(2, y);

    deleteBoard(board, W);
}

TEST(TwoPixelsTestSuite_links, Unitary) {
    int W = 0;
    int H = 0;

    Color **board = createTestBoard(&W, &H, 2);
    Direction **links = createEmptyLinks(W, H);

    int x = 1;
    int y = 1;
    EXPECT_EQ(Direction::none, links[1][1]);
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::right_cmd));
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

    Color **board = createTestBoard(&W, &H, 2);
    Direction **links = createEmptyLinks(W, H);

    int x = 1;
    int y = 1;
    EXPECT_EQ(Direction::none, links[1][1]);
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::right_cmd));
    EXPECT_EQ(Direction::right_dir, links[1][1]);
    EXPECT_EQ(2, x);
    EXPECT_EQ(1, y);
    EXPECT_EQ(Direction::end, links[2][1]);

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::up_cmd));
    EXPECT_EQ(Direction::up_dir, links[2][1]);
    EXPECT_EQ(2, x);
    EXPECT_EQ(0, y);
    EXPECT_EQ(Direction::end, links[2][0]);

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::left_cmd));
    EXPECT_EQ(Direction::left_dir, links[2][0]);
    EXPECT_EQ(1, x);
    EXPECT_EQ(0, y);
    EXPECT_EQ(Direction::end, links[1][0]);

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::left_cmd));
    EXPECT_EQ(Direction::left_dir, links[1][0]);
    EXPECT_EQ(0, x);
    EXPECT_EQ(0, y);
    EXPECT_EQ(Direction::end, links[0][0]);

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::down_cmd));
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

    Color **board = createTestBoard(&W, &H, 3);
    Direction **links = createEmptyLinks(W, H);

    int x = 1;
    int y = 1;
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::right_cmd));
    EXPECT_EQ(Direction::none, links[1][1]);
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::up_cmd));
    EXPECT_EQ(Direction::none, links[1][1]);
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::left_cmd));
    EXPECT_EQ(Direction::none, links[1][1]);
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::down_cmd));
    EXPECT_EQ(Direction::none, links[1][1]);
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);

    deleteBoard(board, W);
    deleteLinks(links, W);

}

TEST(TwoPixelsTestSuite_links, KOForBorders) {
    int W = 0;
    int H = 0;

    Color **board = createTestBoard(&W, &H, 3);
    Direction **links = createEmptyLinks(W, H);
    int x = 0;
    int y = 0;
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::left_cmd));
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

    Color **board = createTestBoard(&W, &H, 2);
    Direction **links = createEmptyLinks(W, H);

    links[0][1] = Direction::right_dir;
    links[1][1] = Direction::right_dir;
    links[2][1] = Direction::end;
    int x = 2;
    int y = 1;
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::left_cmd));
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
    EXPECT_TRUE(isAlone(links, W, H, 0, H - 1));
    EXPECT_TRUE(isAlone(links, W, H, W - 1, 0));
}

TEST(TwoPixelsTestSuite_links, isNotAlone) {
    int W = 3;
    int H = 4;

    Direction **links = createEmptyLinks(W, H);

    links[1][1] = Direction::left_dir;
    links[1][2] = Direction::left_dir;

    //EXPECT_FALSE(isAlone(links, W, H, 1, 1));
    EXPECT_FALSE(isAlone(links, W, H, 0, H - 1));
    EXPECT_FALSE(isAlone(links, W, H, W - 1, 0));
}

TEST(TwoPixelsTestSuite_links, RewindToNone) {
    int W = 0;
    int H = 0;

    Color **board = createTestBoard(&W, &H, 2);
    Direction **links = createEmptyLinks(W, H);

    links[1][1] = Direction::right_dir;
    links[2][1] = Direction::end;
    int x = 2;
    int y = 1;
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::left_cmd));
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_EQ(Direction::none, links[2][1]);
    EXPECT_EQ(Direction::none, links[1][1]);

    links[1][1] = Direction::left_dir;
    links[0][1] = Direction::end;
    x = 0;
    y = 1;
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::right_cmd));
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_EQ(Direction::none, links[0][1]);
    EXPECT_EQ(Direction::none, links[1][1]);

    links[1][1] = Direction::up_dir;
    links[1][0] = Direction::end;
    x = 1;
    y = 0;
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::down_cmd));
    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);
    EXPECT_EQ(Direction::none, links[1][0]);
    EXPECT_EQ(Direction::none, links[1][1]);

    links[1][1] = Direction::down_dir;
    links[1][2] = Direction::end;
    x = 1;
    y = 2;
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::up_cmd));
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

    Color **board = createTestBoard(&W, &H, 2);
    Direction **links = createEmptyLinks(W, H);

    links[1][1] = Direction::left_dir;
    links[0][1] = Direction::down_dir;
    links[0][2] = Direction::right_dir;
    int x = 1;
    int y = 1;

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::right_cmd));
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::down_cmd));
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::left_cmd));
    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::up_cmd));


    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::up_cmd));
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::left_cmd));
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::right_cmd));

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::down_cmd));
    EXPECT_EQ(Direction::right_dir, links[1][1]);
    EXPECT_EQ(Direction::none, links[1][2]);

}

TEST(TwoPixelsTestSuite_cycle, should_not_be_able_to_come_back) {
    int W = 0;
    int H = 0;

    Color **board = createTestBoard(&W, &H, 2);
    Direction **links = createEmptyLinks(W, H);

    int x = 0;
    int y = 1;

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::right_cmd));
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::right_cmd));
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::down_cmd));
    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::left_cmd));
    EXPECT_EQ(1, x);
    EXPECT_EQ(2, y);

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::up_cmd));

    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::up_cmd));
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::left_cmd));
    EXPECT_FALSE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::right_cmd));

    EXPECT_TRUE(linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::down_cmd));
    EXPECT_EQ(Direction::right_dir, links[1][1]);
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

    Color **board = createTestBoard(&W, &H, 4);
    Direction **links = createEmptyLinks(W, H);


    EXPECT_FALSE(consumeLinks(board, links, W, H));

    int x = 0;
    int y = 2;
    linkAndMoveIfLegit(board, links, W, H, &x, &y, Command::right_cmd);

    EXPECT_TRUE(consumeLinks(board, links, W, H));

    //EXPECT_EQ(OMEGA, board[0][0]); Random now :(
    //EXPECT_EQ(OMEGA, board[1][0]); Random now :(
    EXPECT_EQ(ALPHA, board[0][1]);
    EXPECT_EQ(BETA, board[1][1]);
    EXPECT_EQ(GAMMA, board[0][2]);
    EXPECT_EQ(DELTA, board[1][2]);
}


TEST(TwoPixelsTestSuite_shiftDown, trivial) {
    int W = 0;
    int H = 0;

    Color **board = createTestBoard(&W, &H, 4);

    shiftDown(board, 0, 0);

    EXPECT_EQ(OMEGA, board[0][0]);
}

TEST(TwoPixelsTestSuite_shiftDown, oneFloor) {
    int W = 0;
    int H = 0;

    Color **board = createTestBoard(&W, &H, 4);
    EXPECT_EQ(BETA, board[1][0]);

    shiftDown(board, 1, 1);

    //EXPECT_EQ(OMEGA, board[1][0]); Random now :(
    EXPECT_EQ(BETA, board[1][1]);
}

TEST(TwoPixelsTestSuite_shiftDown, twoFloors) {
    int W = 0;
    int H = 0;

    Color **board = createTestBoard(&W, &H, 4);
    EXPECT_EQ(BETA, board[1][0]);
    EXPECT_EQ(DELTA, board[1][1]);

    shiftDown(board, 1, 2);

    //EXPECT_EQ(OMEGA, board[1][0]); Random now :(
    EXPECT_EQ(BETA, board[1][1]);
    EXPECT_EQ(DELTA, board[1][2]);
}

TEST(TwoPixelsTestSuite, map) {
    EXPECT_EQ(map(Direction::right_dir), Command::right_cmd);
    EXPECT_EQ(map(Direction::left_dir), Command::left_cmd);
    EXPECT_EQ(map(Direction::up_dir), Command::up_cmd);
    EXPECT_EQ(map(Direction::down_dir), Command::down_cmd);
    EXPECT_EQ(map(Direction::right_lock), Command::right_cmd);
    EXPECT_EQ(map(Direction::left_lock), Command::left_cmd);
    EXPECT_EQ(map(Direction::up_lock), Command::up_cmd);
    EXPECT_EQ(map(Direction::down_lock), Command::down_cmd);
    EXPECT_EQ(map(Command::right_cmd), Direction::right_dir);
    EXPECT_EQ(map(Command::left_cmd), Direction::left_dir);
    EXPECT_EQ(map(Command::up_cmd), Direction::up_dir);
    EXPECT_EQ(map(Command::down_cmd), Direction::down_dir);
}

TEST(TwoPixelsTestSuite, countPositionsIShouldShiftDown) {
    Direction **links = createEmptyLinks(5, 3);
    /*
     *  |  t | xt |  t | xt |  t |
     *  |    |  t | xt | xt | x  |
     *  |    |    |    |    | xt |
     */
    links[1][0] = Direction::up_dir;
    links[2][1] = Direction::up_dir;
    links[3][0] = Direction::up_dir;
    links[3][1] = Direction::up_dir;
    links[4][1] = Direction::up_dir;
    links[4][2] = Direction::up_dir;

    EXPECT_EQ(0, countPositionsIShouldShiftDown(links, 3, 3, 0, 0));
    EXPECT_EQ(1, countPositionsIShouldShiftDown(links, 3, 3, 1, 0));
    EXPECT_EQ(0, countPositionsIShouldShiftDown(links, 3, 3, 1, 1));
    EXPECT_EQ(1, countPositionsIShouldShiftDown(links, 3, 3, 2, 0));
    EXPECT_EQ(1, countPositionsIShouldShiftDown(links, 3, 3, 2, 1));
    EXPECT_EQ(2, countPositionsIShouldShiftDown(links, 3, 3, 3, 0));
    EXPECT_EQ(2, countPositionsIShouldShiftDown(links, 3, 3, 3, 1));
    EXPECT_EQ(2, countPositionsIShouldShiftDown(links, 3, 3, 4, 0));
    EXPECT_EQ(2, countPositionsIShouldShiftDown(links, 3, 3, 4, 2));

}


TEST(TwoPixelsTestSuite_distribution, no_reorder) {

    /**
     * dans l'ordre de distribution
     * puis dans l'ordre alphabétique grec
     */
    int currentDistributions[] = {0, 0, 0, 0, 0};
    Color distributionColorOrder[] = {ALPHA, BETA, GAMMA, DELTA, OMEGA};

    int W = 1;
    int H = 15;

    Color boardLine[] =
            {ALPHA,
             BETA, BETA,
             GAMMA, GAMMA, GAMMA,
             DELTA, DELTA, DELTA, DELTA,
             OMEGA, OMEGA, OMEGA, OMEGA, OMEGA};
    Color *boardArray[] = {static_cast<Color *>(boardLine)};
    Color **board = static_cast<Color **>(boardArray);

    updateDistributions(board, W, H, currentDistributions, distributionColorOrder, 15);
    ASSERT_THAT(currentDistributions, ElementsAre(1, 2, 3, 4, 5));
    ASSERT_THAT(distributionColorOrder, ElementsAre(ALPHA, BETA, GAMMA, DELTA, OMEGA));
}

TEST(TwoPixelsTestSuite_distribution, reorder) {

    /**
     * dans l'ordre de distribution
     * puis dans l'ordre alphabétique grec
     */
    int currentDistributions[] = {0, 0, 0, 0, 0};
    Color distributionColorOrder[] = {ALPHA, BETA, GAMMA, DELTA, OMEGA};

    int W = 1;
    int H = 15;

    Color boardLine[] =
            {ALPHA, ALPHA, ALPHA, ALPHA, ALPHA,
             BETA, BETA, BETA, BETA,
             GAMMA, GAMMA, GAMMA,
             DELTA, DELTA,
             OMEGA};
    Color *boardArray[] = {static_cast<Color *>(boardLine)};
    Color **board = static_cast<Color **>(boardArray);

    updateDistributions(board, W, H, currentDistributions, distributionColorOrder, 15);
    ASSERT_THAT(currentDistributions, ElementsAre(1, 2, 3, 4, 5));
    ASSERT_THAT(distributionColorOrder, ElementsAre(OMEGA, DELTA, GAMMA, BETA, ALPHA));
}

TEST(TwoPixelsTestSuite_distribution, reorder_with_equality) {

    /**
     * dans l'ordre de distribution
     * puis dans l'ordre alphabétique grec
     */
    int currentDistributionsA[5];
    Color distributionColorOrderA[5];
    int currentDistributionsB[5];
    Color distributionColorOrderB[5];

    int W = 1;
    int H = 15;

    Color boardLineA[] =
            {ALPHA, ALPHA, ALPHA, ALPHA, ALPHA,
             BETA, BETA, BETA, BETA,
             GAMMA, GAMMA,
             DELTA, DELTA,
             OMEGA};
    Color boardLineB[] =
            {ALPHA,
             BETA, BETA,
             GAMMA, GAMMA, GAMMA,
             DELTA, DELTA, DELTA,
             OMEGA, OMEGA, OMEGA, OMEGA, OMEGA};
    Color *boardArrayA[] = {static_cast<Color *>(boardLineA)};
    Color **boardA = static_cast<Color **>(boardArrayA);
    Color *boardArrayB[] = {static_cast<Color *>(boardLineB)};
    Color **boardB = static_cast<Color **>(boardArrayB);

    updateDistributions(boardA, W, H, currentDistributionsA, distributionColorOrderA, 15);
    updateDistributions(boardB, W, H, currentDistributionsB, distributionColorOrderB, 15);
    ASSERT_THAT(currentDistributionsA, ElementsAre(1, 2, 2, 4, 5));
    ASSERT_THAT(distributionColorOrderA, ElementsAre(OMEGA, GAMMA, DELTA, BETA, ALPHA));
    ASSERT_THAT(currentDistributionsB, ElementsAre(1, 2, 3, 3, 5));
    ASSERT_THAT(distributionColorOrderB, ElementsAre(ALPHA, BETA, GAMMA, DELTA, OMEGA));
}

TEST(TwoPixelsTestSuite_distribution, rounding) {
    int currentDistributions[] = {0, 0, 0, 0, 0};
    Color distributionColorOrder[] = {ALPHA, BETA, GAMMA, DELTA, OMEGA};

    int W = 0;
    int H = 0;
    

    Color **board = createTestBoard(&W, &H, 3);
    updateDistributions(board, W, H, currentDistributions, distributionColorOrder, 10);
    ASSERT_THAT(currentDistributions, ElementsAre(0, 0, 0, 1, 9));

}

/**
 * Score : pièces de couleur en fonction des objectifs atteints
 */

TEST(TwoPixelsTestSuite_distribution, sort) {
    DistributionElement distributionElements[5];
    for (int k = 0; k < COLOR_COUNT; ++k) {
        DistributionElement element;
        element.color = all_colors[k];
        element.count = 4-k;
        distributionElements[k] = element;
    }

    sortDistributionElements(distributionElements);

    Color orderedColors[5];
    for (int k = 0; k < COLOR_COUNT; ++k) {
        orderedColors[k] = distributionElements[k].color;
    }

    ASSERT_THAT(orderedColors, ElementsAre(OMEGA, DELTA, GAMMA, BETA, ALPHA));
}

TEST(TwoPixelsTestSuite, indexOfColor) {
    EXPECT_EQ(0, indexOf(ALPHA));
    EXPECT_EQ(1, indexOf(BETA));
    EXPECT_EQ(2, indexOf(GAMMA));
    EXPECT_EQ(3, indexOf(DELTA));
    EXPECT_EQ(4, indexOf(OMEGA));
}

TEST(TwoPixelsTestSuite_score, low) {
    bool score[3*COLOR_COUNT];
    for (int i = 0; i < 3 * COLOR_COUNT; ++i) {
        score[i] = false;
    }

    int W = 1;
    const int H = 100;

    Color boardLine[H];
    for (int j = 0; j < H; ++j) {
        if (j < 6) boardLine[j] = GAMMA;
        else if (j < 80) boardLine[j] = BETA;
        else boardLine[j] = DELTA;
    }

    Color *boardArray[] = {static_cast<Color *>(boardLine)};
    Color **board = static_cast<Color **>(boardArray);

    updateScore(board, W, H, score);
    ASSERT_FALSE(score[6]);

    board[0][5] = BETA;
    updateScore(board, W, H, score);
    ASSERT_TRUE(score[6]);
}

TEST(TwoPixelsTestSuite_score, medium) {
    bool score[3*COLOR_COUNT];
    for (int i = 0; i < 3 * COLOR_COUNT; ++i) {
        score[i] = false;
    }

    int W = 1;
    const int H = 100;

    Color boardLine[H];
    for (int j = 0; j < H; ++j) {
        if (j < 49) boardLine[j] = ALPHA;
        else if (j < 80) boardLine[j] = BETA;
        else boardLine[j] = DELTA;
    }

    Color *boardArray[] = {static_cast<Color *>(boardLine)};
    Color **board = static_cast<Color **>(boardArray);

    updateScore(board, W, H, score);
    ASSERT_FALSE(score[1]);

    board[0][49] = ALPHA;
    updateScore(board, W, H, score);
    ASSERT_TRUE(score[1]);
}

TEST(TwoPixelsTestSuite_score, high) {
    bool score[15]; //3 * COLOR_COUNT
    for (int i = 0; i < 15; ++i) {
        score[i] = false;
    }

    int W = 1;
    const int H = 100;

    Color boardLine[H];
    for (int j = 0; j < H; ++j) {
        if (j < 79) boardLine[j] = OMEGA;
        else if (j < 95) boardLine[j] = BETA;
        else boardLine[j] = DELTA;
    }

    Color *boardArray[] = {static_cast<Color *>(boardLine)};
    Color **board = static_cast<Color **>(boardArray);

    updateScore(board, W, H, score);
    ASSERT_FALSE(score[14]);

    board[0][80] = OMEGA;
    updateScore(board, W, H, score);
    ASSERT_TRUE(score[14]);
}

TEST(TwoPixelsTestSuite, sandbox) {
    EXPECT_EQ(-1 % 4, -1);
}