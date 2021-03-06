#include <map>
#include <iostream>
#include <functional>

class chessboard {
public:
    enum { CHESS_BOARD_SIZE = 8 };

    chessboard() : m_squares(CHESS_BOARD_SIZE, std::vector<square>(CHESS_BOARD_SIZE)) {}
    ~chessboard() {}

    char get_chess_at(unsigned int x, unsigned int y) { return m_squares[x][y].chess; }
    size_t calculate_unattacked_count();

    friend std::istream & operator >> (std::istream &is, chessboard &rhs);

private:
    struct square {
        char chess;
        unsigned short attacked_count;
    };
    std::vector<std::vector<square>> m_squares;

    static void pawn(size_t, size_t, std::vector<std::vector<square>>&, bool);
    static void knight(size_t, size_t, std::vector<std::vector<square>>&);
    static void bishop(size_t, size_t, std::vector<std::vector<square>>&);
    static void castle(size_t, size_t, std::vector<std::vector<square>>&);
    static void queen(size_t, size_t, std::vector<std::vector<square>>&);
    static void king(size_t, size_t, std::vector<std::vector<square>>&);

    const static std::map<char, std::function<void(size_t, size_t, std::vector<std::vector<square>>&)>> ATTACK_PATTERNS;
};