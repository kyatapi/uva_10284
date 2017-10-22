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

