#include <iostream>

class chessboard {
public:
    chessboard() {}
    ~chessboard() {}

    char get_chess_at(unsigned int x, unsigned int y) { return '\0'; }

    friend std::istream & operator >> (std::istream &is, chessboard &rhs);
};