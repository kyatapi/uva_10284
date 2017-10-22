#include <iostream>

class chessboard {
public:
    chessboard() : m_squares(CHESS_BOARD_SIZE, std::vector<char>(CHESS_BOARD_SIZE)) {}
    ~chessboard() {}

    char get_chess_at(unsigned int x, unsigned int y) { return m_squares[x][y]; }

    friend std::istream & operator >> (std::istream &is, chessboard &rhs);

private:
    enum { CHESS_BOARD_SIZE = 8 };
    std::vector<std::vector<char>> m_squares;
};