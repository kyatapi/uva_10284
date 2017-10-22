#ifndef ONLINE_JUDGE
#include "test_cases.h"
extern void run_test(int argc, char **argv);
#else
inline void run_test(int argc, char **argv) {}
#endif // !ONLINE_JUDGE

#include "chess.h"

using namespace std;

istream & operator >> (istream &is, chessboard &rhs) {
    static const string VALID_CHESS_LETTERS("pnbrqkPNBRQK");

    for (unsigned int y = 0; y < chessboard::CHESS_BOARD_SIZE; ++y) {
        string row;
        getline(is, row, '/');
        unsigned int x = 0;
        for (size_t c = 0; c < row.size(); ++c) {
            if (isdigit(row[c])) {
                x += (row[c] - '0');
            }
            else if (VALID_CHESS_LETTERS.find(row[c]) >= 0) {
                rhs.m_squares[x][y] = row[c];
            }
        }
    }
    return is;
}

int main(int argc, char** argv) {
    run_test(argc, argv);
    return 0;
}