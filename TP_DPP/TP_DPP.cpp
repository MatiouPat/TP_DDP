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

class Square
{
public:
    Square(int _cost, int _heuristic, SquareState _state)
    {
        cost = _cost;
        heuristic = _heuristic;
        state = _state;
    }
    SquareState getState()
    {
        return state;
    }
    int getHeuristic()
    {
        return heuristic;
    }
    int getCost()
    {
        return cost;
    }
private:
    int cost;
    int heuristic;
    SquareState state;
};

class Board
{
public:
    Board(int _sizeX, int _sizeY)
    {
        sizeX = _sizeX;
        sizeY = _sizeY;
        board = std::deque<std::deque<Square>>(_sizeY, std::deque<Square>(_sizeX, Square{ 0, 0, SquareState::UNKNOWN }));
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
                row.push_front(Square{ 0, 0, SquareState::UNKNOWN });
            }
            sizeX++;
            break;
        }
        case NORTH:
        {
            std::deque<Square> newRow(sizeX, Square{ 0, 0, SquareState::UNKNOWN });
            board.push_front(newRow);
            sizeY++;
            break;
        }
        case EAST:
        {
            for (auto& row : board) {
                row.push_back(Square{ 0, 0, SquareState::UNKNOWN });
            }
            sizeX++;
            break;
        }
        case SOUTH:
        {
            std::deque<Square> newRow(sizeX, Square{ 0, 0, SquareState::UNKNOWN });
            board.push_front(newRow);
            sizeY++;
            break;
        }
        case NORTH_WEST:
        {
            for (auto& row : board) {
                row.push_front(Square{ 0, 0, SquareState::UNKNOWN });
            }
            sizeX++;
            std::deque<Square> newRow(sizeX, Square{ 0, 0, SquareState::UNKNOWN });
            board.push_front(newRow);
            sizeY++;
            break;
        }
        case NORTH_EAST:
        {
            for (auto& row : board) {
                row.push_back(Square{ 0, 0, SquareState::UNKNOWN });
            }
            sizeX++;
            std::deque<Square> newRow(sizeX, Square{ 0, 0, SquareState::UNKNOWN });
            board.push_front(newRow);
            sizeY++;
            break;
        }
        case SOUTH_WEST:
        {
            for (auto& row : board) {
                row.push_front(Square{ 0, 0, SquareState::UNKNOWN });
            }
            sizeX++;
            std::deque<Square> newRow(sizeX, Square{ 0, 0, SquareState::UNKNOWN });
            board.push_front(newRow);
            sizeY++;
            break;
        }
        case SOUTH_EAST:
        {
            for (auto& row : board) {
                row.push_back(Square{ 0, 0, SquareState::UNKNOWN });
            }
            sizeX++;
            std::deque<Square> newRow(sizeX, Square{ 0, 0, SquareState::UNKNOWN });
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
        for (auto& row : board)
        {
            for (auto& square : row)
            {
                char symbol;
                switch (square.getState())
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
                std::cout << symbol << square.getHeuristic() << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    void searchShortestPath(int startX, int startY, int endX, int endY)
    {
        board[startX][startY] = Square{ 0, 0,  SquareState::TRAVERSABLE };
        board[endX][endY] = Square{ 0, 0,  SquareState::TRAVERSABLE };
        board[2][1] = Square{ 0, 0,  SquareState::UNTRAVERSABLE };
        board[2][2] = Square{ 0, 0,  SquareState::UNTRAVERSABLE };
    }
    /*
    * On compare la distance entre s1 et dest et s2 et dest
    * Si s1 est plus près que s2 -> 1
    * Si s1 est plus près que s2 -> 0
    * Si s1 est plus près que s2 -> 1
    */
    int calculHeuristic(int s1X, int s1Y, int s2X, int s2Y, int destX, int destY)
    {
        if ((destX - s1X < destX - s2X) || (destY - s1Y < destY - s2Y))
        {
            return 1;
        }
        else if ((destX - s1X == destX - s2X) && (destY - s1Y == destY - s2Y))
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }

    std::shared_ptr<std::deque<Square>> neighbours(int squareX, int squareY)
    {
        ptrNeighboursList = std::shared_ptr<std::deque<Square>>;
        
        switch (squareX)
        {
        case 0:
            addChessboardCase(NORTH);
            break;
        case sizeX:
            addChessboardCase(SOUTH);
            break;
        }

        switch(squareY)
        {
        case 0:
            addChessboardCase(WEST);
            break;
        case sizeY:
            addChessboardCase(EAST);
            break;
        }

        (*ptrNeighboursList).push_front(bord[squareX - 1][squareY - 1]);
        (*ptrNeighboursList).push_front(bord[squareX-1][squareY ]);
        (*ptrNeighboursList).push_front(bord[squareX - 1][squareY+ 1]);
        (*ptrNeighboursList).push_front(bord[squareX ][squareY - 1]);
        (*ptrNeighboursList).push_front(bord[squareX ][squareY]);
        (*ptrNeighboursList).push_front(bord[squareX ][squareY + 1]);
        (*ptrNeighboursList).push_front(bord[squareX + 1][squareY - 1]);
        (*ptrNeighboursList).push_front(bord[squareX + 1][squareY]);
        (*ptrNeighboursList).push_front(bord[squareX + 1][squareY + 1]);

        return ptrNeighboursList;
    }

private:
    int sizeX;
    int sizeY;
    std::deque<std::deque<Square>> board;
};

int main()
{
    std::shared_ptr<Board> board = std::shared_ptr<Board>(new Board(5, 5));
    //board->printChessboard();
    board->searchShortestPath(1, 1, 4, 4);
}