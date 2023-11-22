#include <iostream>
#include <deque>

enum SquareState
{
    UNKNOWN = 0,
    TRAVERSABLE = 1,
    UNTRAVERSABLE = 2
};

enum Orientation
{
    WEST = 0,
    NORTH = 1,
    EAST = 2,
    SOUTH = 3
};

/**
* Print
*/
void printChessboard(const std::deque<std::deque<SquareState>>& chessboard)
{
    for (const auto& row : chessboard)
    {
        for (const auto& square : row)
        {
            char symbol;
            switch (square)
            {
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

/**
* 0-Left / 1-Top / 2-Right / 3-Bottom
*/
void addChessboardCase(std::deque<std::deque<SquareState>>& chessboard, Orientation orientation, int& sizeX, int& sizeY)
{
    switch (orientation)
    {
    case WEST:
    {
        for(auto& row : chessboard) {
            row.push_front(SquareState::UNKNOWN);
        }
        sizeX++;
        break;
    }
    case NORTH:
    {
        std::deque<SquareState> newRow(sizeX, SquareState::UNKNOWN);
        chessboard.push_front(newRow);
        sizeY++;
        break;
    }
    case EAST:
    {
        for (auto& row : chessboard) {
            row.push_back(SquareState::UNKNOWN);
        }
        sizeX++;
        break;
    }
    case SOUTH:
    {
        std::deque<SquareState> newRow(sizeX, SquareState::UNKNOWN);
        chessboard.push_front(newRow);
        sizeY++;
        break;
    }
    }
}

int main()
{
    int sizeX = 10;
    int sizeY = 10;
    std::deque<std::deque<SquareState>> board(sizeY, std::deque<SquareState>(sizeX, SquareState::UNKNOWN));
    board[0][0] = SquareState::TRAVERSABLE;
    addChessboardCase(board, Orientation::WEST, sizeX, sizeY);
    addChessboardCase(board, Orientation::NORTH, sizeX, sizeY);
    printChessboard(board);
}