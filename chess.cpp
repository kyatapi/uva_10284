#ifndef ONLINE_JUDGE
#include "test_cases.h"
extern void run_test(int argc, char **argv);
#else
inline void run_test(int argc, char **argv) {}
#endif // !ONLINE_JUDGE

#include "chess.h"

using namespace std;
using namespace std::placeholders;

istream & operator >> (istream &is, chessboard &rhs) {
    static const string VALID_CHESS_LETTERS("pnbrqkPNBRQK");

    rhs.m_squares = vector<vector<chessboard::square>>(chessboard::CHESS_BOARD_SIZE, vector<chessboard::square>(chessboard::CHESS_BOARD_SIZE));
    for (unsigned int y = 0; y < chessboard::CHESS_BOARD_SIZE; ++y) {
        string row;
        getline(is, row, '/');
        size_t x = 0;
        for (char chess : row) {
            if (isdigit(chess)) {
                x += (chess - '0');
            }
            else if (VALID_CHESS_LETTERS.find(chess) >= 0) {
                rhs.m_squares[x][y].chess = chess;
                x++;
            }
        }
    }
    return is;
}

void chessboard::king(size_t x, size_t y, vector<vector<chessboard::square>>& squares) {
    if (x > 0)                                                                                                                                  squares[x - 1][y].attacked_count++;
    if (y > 0)                                                                                                                                  squares[x][y - 1].attacked_count++;
    if (x < chessboard::CHESS_BOARD_SIZE - 1)                                                                          squares[x + 1][y].attacked_count++;
    if (y < chessboard::CHESS_BOARD_SIZE - 1)                                                                          squares[x][y + 1].attacked_count++;
    if (x > 0 && y > 0)                                                                                                                  squares[x - 1][y - 1].attacked_count++;
    if (x < chessboard::CHESS_BOARD_SIZE - 1 && y > 0)                                                          squares[x + 1][y - 1].attacked_count++;
    if (x > 0 && y < chessboard::CHESS_BOARD_SIZE - 1)                                                          squares[x - 1][y + 1].attacked_count++;
    if (x < chessboard::CHESS_BOARD_SIZE - 1 && y < chessboard::CHESS_BOARD_SIZE - 1)  squares[x + 1][y + 1].attacked_count++;
}

void chessboard::knight(size_t x, size_t y, vector<vector<chessboard::square>>& squares) {
    if (x > 0 && y > 1)                                                                                                                  squares[x - 1][y - 2].attacked_count++;
    if (x > 0 && y < chessboard::CHESS_BOARD_SIZE - 2)                                                          squares[x - 1][y + 2].attacked_count++;
    if (x < chessboard::CHESS_BOARD_SIZE - 1 && y > 1)                                                          squares[x + 1][y - 2].attacked_count++;
    if (x < chessboard::CHESS_BOARD_SIZE - 1 && y < chessboard::CHESS_BOARD_SIZE - 2)  squares[x + 1][y + 2].attacked_count++;
    if (x > 1 && y > 0)                                                                                                                  squares[x - 2][y - 1].attacked_count++;
    if (x < chessboard::CHESS_BOARD_SIZE - 2 && y > 0)                                                          squares[x + 2][y - 1].attacked_count++;
    if (x > 1 && y < chessboard::CHESS_BOARD_SIZE - 1)                                                          squares[x - 2][y + 1].attacked_count++;
    if (x < chessboard::CHESS_BOARD_SIZE - 2 && y < chessboard::CHESS_BOARD_SIZE - 1)  squares[x + 2][y + 1].attacked_count++;
}

void chessboard::bishop(size_t x, size_t y, vector<vector<chessboard::square>>& squares) {
    static function<bool(int, int, vector<vector<chessboard::square>>&)> update_board = [](int dx, int dy, vector<vector<chessboard::square>>& squares) {
        if (dy < 0 || dy >= CHESS_BOARD_SIZE) return true;
        if (squares[dx][dy].chess) return false;

        squares[dx][dy].attacked_count++;
        return true;
    };

    for (int dx = x - 1; dx >= 0; --dx) {
        int dy = y - x + dx;
        if (!update_board(dx, dy, squares)) break;
    }

    for (int dx = x + 1; dx < CHESS_BOARD_SIZE; ++dx) {
        int dy = y - x + dx;
        if (!update_board(dx, dy, squares)) break;
    }

    for (int dx = x - 1; dx >= 0; --dx) {
        int dy = y + x - dx;
        if (!update_board(dx, dy, squares)) break;
    }

    for (int dx = x + 1; dx < CHESS_BOARD_SIZE; ++dx) {
        int dy = y + x - dx;
        if (!update_board(dx, dy, squares)) break;
    }
}

void chessboard::castle(size_t x, size_t y, vector<vector<chessboard::square>>& squares) {
    for (int d = x -1 ; d >= 0; --d) {
        if (squares[d][y].chess) break;
        squares[d][y].attacked_count++;
    }

    for (int d = y - 1; d >= 0; --d) {
        if (squares[x][d].chess) break;
        squares[x][d].attacked_count++;
    }

    for (int d = x + 1; d < CHESS_BOARD_SIZE; ++d) {
        if (squares[d][y].chess) break;
        squares[d][y].attacked_count++;
    }

    for (int d = y + 1; d < CHESS_BOARD_SIZE; ++d) {
        if (squares[x][d].chess) break;
        squares[x][d].attacked_count++;
    }
}

void chessboard::queen(size_t x, size_t y, vector<vector<chessboard::square>>& squares) {
    castle(x, y, squares);
    bishop(x, y, squares);
}

void chessboard::pawn(size_t x, size_t y, std::vector<std::vector<chessboard::square>>& squares, bool black) {
    if (black && y <chessboard::CHESS_BOARD_SIZE - 1) {
        if (x > 0) squares[x - 1][y + 1].attacked_count++;
        if (x < chessboard::CHESS_BOARD_SIZE - 1) squares[x + 1][y + 1].attacked_count++;
    }
    else if (!black && y > 0) {
        if (x > 0) squares[x - 1][y - 1].attacked_count++;
        if (x < chessboard::CHESS_BOARD_SIZE - 1) squares[x + 1][y - 1].attacked_count++;
    }
}

const map<char, function<void(size_t, size_t, vector<vector<chessboard::square>>&)>> chessboard::ATTACK_PATTERNS = {
    { 'P', bind(chessboard::pawn, _1, _2, _3, false) },
    { 'N', chessboard::knight },
    { 'B', chessboard::bishop },
    { 'R', chessboard::castle },
    { 'Q', chessboard::queen },
    { 'K', chessboard::king },
    { 'p', bind(chessboard::pawn, _1, _2, _3, true) },
    {'n', chessboard::knight},
    { 'b', chessboard::bishop},
    { 'r', chessboard::castle},
    { 'q', chessboard::queen},
    { 'k', chessboard::king }
};

size_t chessboard::calculate_unattacked_count() {
    for (size_t y = 0; y < CHESS_BOARD_SIZE; ++y) {
        for (size_t x = 0; x < CHESS_BOARD_SIZE; ++x) {
            if (m_squares[x][y].chess) {
                m_squares[x][y].attacked_count++;
                ATTACK_PATTERNS.at(m_squares[x][y].chess)(x, y, m_squares);
            }
        }
    }

    size_t unattacked = 0;
    for (size_t x = 0; x < CHESS_BOARD_SIZE; ++x) {
        unattacked += count_if(m_squares[x].begin(), m_squares[x].end(), [](square s) { return s.attacked_count == 0; });
    }
    return unattacked;
}

int main(int argc, char** argv) {
    run_test(argc, argv);

    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        chessboard board;
        iss >> board;
        cout << board.calculate_unattacked_count() << endl;
    }

    return 0;
}