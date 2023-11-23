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
    WEST = 1,
    NORTH = 2,
    NORTH_WEST = 3,
    EAST = 4,
    NORTH_EAST = 6,
    SOUTH = 8,
    SOUTH_WEST = 9,
    SOUTH_EAST = 12
};

class Board
{
public:
    Board(int _sizeX, int _sizeY)
    {
        sizeX = _sizeX;
        sizeY = _sizeY;
        board = std::deque<std::deque<SquareState>>(_sizeY, std::deque<SquareState>(_sizeX, SquareState::UNKNOWN));
        board[0][0] = SquareState::TRAVERSABLE;
    }
    /**
    * 0-Left : 0001 / 1-Top : 0010 / 2-Right : 0100 / 3-Bottom : 1000
    */
    void addChessboardCase(Orientation orientation)
    {
        switch (orientation)
        {
        case WEST:
        {
            for (auto& row : board) {
                row.push_front(SquareState::UNKNOWN);
            }
            sizeX++;
            break;
        }
        case NORTH:
        {
            std::deque<SquareState> newRow(sizeX, SquareState::UNKNOWN);
            board.push_front(newRow);
            sizeY++;
            break;
        }
        case EAST:
        {
            for (auto& row : board) {
                row.push_back(SquareState::UNKNOWN);
            }
            sizeX++;
            break;
        }
        case SOUTH:
        {
            std::deque<SquareState> newRow(sizeX, SquareState::UNKNOWN);
            board.push_front(newRow);
            sizeY++;
            break;
        }
        case NORTH_WEST:
        {
            for (auto& row : board) {
                row.push_front(SquareState::UNKNOWN);
            }
            sizeX++;
            std::deque<SquareState> newRow(sizeX, SquareState::UNKNOWN);
            board.push_front(newRow);
            sizeY++;
            break;
        }
        case NORTH_EAST:
        {
            for (auto& row : board) {
                row.push_back(SquareState::UNKNOWN);
            }
            sizeX++;
            std::deque<SquareState> newRow(sizeX, SquareState::UNKNOWN);
            board.push_front(newRow);
            sizeY++;
            break;
        }
        case SOUTH_WEST:
        {
            for (auto& row : board) {
                row.push_front(SquareState::UNKNOWN);
            }
            sizeX++;
            std::deque<SquareState> newRow(sizeX, SquareState::UNKNOWN);
            board.push_front(newRow);
            sizeY++;
            break;
        }
        case SOUTH_EAST:
        {
            for (auto& row : board) {
                row.push_back(SquareState::UNKNOWN);
            }
            sizeX++;
            std::deque<SquareState> newRow(sizeX, SquareState::UNKNOWN);
            board.push_front(newRow);
            sizeY++;
            break;
        }
        }
    }
    /**
    * Print
    */
    void printChessboard()
    {
        for (const auto& row : board)
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
        std::cout << '\n';
    }
private:
    int sizeX;
    int sizeY;
    std::deque<std::deque<SquareState>> board;
};

int main()
{
    std::shared_ptr<Board> board = std::shared_ptr<Board>(new Board(10, 10));
    board->printChessboard();
    board->addChessboardCase(Orientation::NORTH_WEST);
    board->printChessboard();
}