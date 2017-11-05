#include <sstream>
#include "test_cases.h"
#include "chess.h"

using namespace std;

TEST(ReadFromFEN, HandleEmpty) {
    istringstream iss("8/8/8/8/8/8/8/8");
    chessboard board;
    iss >> board;
    ASSERT_EQ(board.get_chess_at(3, 5), '\0');
}

TEST(ReadFromFEN, HandleNormalCase) {
    istringstream iss("8/4k3/8/8/8/8/3K4/8");
    chessboard board;
    iss >> board;
    ASSERT_EQ(board.get_chess_at(3, 5), '\0');
    ASSERT_EQ(board.get_chess_at(4, 1), 'k');
}

TEST(CalculateUnattacked, HandleEmpty) {
    istringstream iss("8/8/8/8/8/8/8/8");
    chessboard board;
    iss >> board;
    ASSERT_EQ(board.calculate_unattacked_count(), 64);
}

TEST(CalculateUnattacked, HandleNoObstacle) {
    istringstream iss("8/4k3/8/8/8/8/3K4/8");
    chessboard board;
    iss >> board;
    ASSERT_EQ(board.calculate_unattacked_count(), 46);

    iss.str("8/8/2n5/8/8/5N2/8/8");
    iss.clear();
    iss >> board;
    ASSERT_EQ(board.calculate_unattacked_count(), 48);

    iss.str("3b4/8/8/8/8/8/8/4B3");
    iss.clear();
    iss >> board;
    ASSERT_EQ(board.calculate_unattacked_count(), 50);

    iss.str("3r4/8/8/8/8/8/8/4R3");
    iss.clear();
    iss >> board;
    ASSERT_EQ(board.calculate_unattacked_count(), 36);
}