#include <iostream>
#include <deque>

enum SquareState
{
    UNKNOWN = 0,
    TRAVERSABLE = 1,
    UNTRAVERSABLE = 2
};

void printChessboard(const std::deque<std::deque<SquareState>>& chessboard) {
    for (const auto& row : chessboard) {
        for (const auto& square : row) {
            char symbol;
            switch (square) {
            case UNKNOWN:
                symbol = '?';
                break;
            case TRAVERSABLE:
                symbol = 'o';
                break;
            case UNTRAVERSABLE:
                symbol = 'x';
                break;
            }
            std::cout << symbol << ' ';
        }
        std::cout << '\n';
    }
}

int main()
{
    std::deque<std::deque<SquareState>> board(10, std::deque<SquareState>(10, SquareState::UNKNOWN));

    printChessboard(board);
}