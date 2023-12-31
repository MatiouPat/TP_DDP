#include <iostream>
#include <deque>
#include <vector>

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
    Square(int _x, int _y, int _cost, int _heuristic, SquareState _state)
    {
        x = _x;
        y = _y;
        cost = _cost;
        heuristic = _heuristic;
        state = _state;
    }
    ~Square()
    {

    }
    int getX()
    {
        return x;
    }
    void setX(int _x)
    {
        x = _x;
    }
    int getY()
    {
        return y;
    }
    void setY(int _y)
    {
        y = _y;
    }
    int getHeuristic()
    {
        return heuristic;
    }
    void setHeuristic(int _heuristic)
    {
        heuristic = _heuristic;
    }
    float getCost()
    {
        return cost;
    }
    void setCost(float _cost)
    {
        cost = _cost;
    }
    SquareState getState()
    {
        return state;
    }
private:
    int x;
    int y;
    float cost;
    int heuristic;
    bool isVisited;
    SquareState state;
};

class Board
{
public:
    Board(int _sizeX, int _sizeY)
    {
        sizeX = _sizeX;
        sizeY = _sizeY;
        board = std::deque<std::deque<std::shared_ptr<Square>>>(_sizeY, std::deque<std::shared_ptr<Square>>(_sizeX));
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                board[i][j] = std::shared_ptr<Square>(new Square(i, j, sizeX + sizeY, sizeX + sizeY, SquareState::UNKNOWN));
            }
        }
    }
    ~Board()
    {

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
            shiftColumns();
            for (int i = 0; i < sizeY; i++) {
                board[i].push_front(std::shared_ptr<Square>(new Square(i, 0, 0, 0, SquareState::UNKNOWN)));
            }
            sizeX++;
            break;
        }
        case NORTH:
        {
            shiftLines();
            std::deque<std::shared_ptr<Square>> newRow;
            for (int i = 0; i < sizeX; i++)
            {
                newRow.push_back(std::shared_ptr<Square>(new Square(0, i, 0, 0, SquareState::UNKNOWN)));
            }
            board.push_front(newRow);
            sizeY++;
            break;
        }
        case EAST:
        {
            for (int i = 0; i < sizeY; i++) {
                board[i].push_back(std::shared_ptr<Square>(new Square(i, sizeX, 0, 0, SquareState::UNKNOWN)));
            }
            sizeX++;
            break;
        }
        case SOUTH:
        {
            std::deque<std::shared_ptr<Square>> newRow;
            for (int i = 0; i < sizeX; i++)
            {
                newRow.push_back(std::shared_ptr<Square>(new Square(sizeY, i, 0, 0, SquareState::UNKNOWN)));
            }
            board.push_back(newRow);
            sizeY++;
            break;
        }
        case NORTH_WEST:
        {
            shiftLinesAndColumns();
            for (int i = 0; i < sizeY; i++) {
                board[i].push_front(std::shared_ptr<Square>(new Square(i + 1, 0, 0, 0, SquareState::UNKNOWN)));
            }
            sizeX++;
            std::deque<std::shared_ptr<Square>> newRow;
            for (int i = 0; i < sizeX; i++)
            {
                newRow.push_back(std::shared_ptr<Square>(new Square(0, i, 0, 0, SquareState::UNKNOWN)));
            }
            board.push_front(newRow);
            sizeY++;
            break;
        }
        case NORTH_EAST:
        {
            shiftLines();
            for (int i = 0; i < sizeY; i++) {
                board[i].push_back(std::shared_ptr<Square>(new Square(i + 1, sizeX, 0, 0, SquareState::UNKNOWN)));
            }
            sizeX++;
            std::deque<std::shared_ptr<Square>> newRow;
            for (int i = 0; i < sizeX; i++)
            {
                newRow.push_back(std::shared_ptr<Square>(new Square(0, i, 0, 0, SquareState::UNKNOWN)));
            }
            board.push_front(newRow);
            sizeY++;
            break;
        }
        case SOUTH_WEST:
        {
            shiftColumns();
            for (int i = 0; i < sizeY; i++) {
                board[i].push_front(std::shared_ptr<Square>(new Square(i, 0, 0, 0, SquareState::UNKNOWN)));
            }
            sizeX++;
            std::deque<std::shared_ptr<Square>> newRow;
            for (int i = 0; i < sizeX; i++)
            {
                newRow.push_back(std::shared_ptr<Square>(new Square(sizeY, i, 0, 0, SquareState::UNKNOWN)));
            }
            board.push_back(newRow);
            sizeY++;
            break;
        }
        case SOUTH_EAST:
        {
            for (int i = 0; i < sizeY; i++) {
                board[i].push_back(std::shared_ptr<Square>(new Square(i, sizeX, 0, 0, SquareState::UNKNOWN)));
            }
            sizeX++;
            std::deque<std::shared_ptr<Square>> newRow;
            for (int i = 0; i < sizeX; i++)
            {
                newRow.push_back(std::shared_ptr<Square>(new Square(sizeY, i, 0, 0, SquareState::UNKNOWN)));
            }
            board.push_back(newRow);
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
        for (std::deque<std::shared_ptr<Square>> row : board)
        {
            for (std::shared_ptr<Square> square : row)
            {
                char symbol;
                switch (square->getState())
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
        std::cout << '\n' << std::endl;
    }
    std::deque < std::shared_ptr<Square>> searchShortestPath(int startX, int startY, int endX, int endY)
    {
        board[startX][startY] = std::shared_ptr<Square>(new Square{ startX, startY, 0, 0, SquareState::TRAVERSABLE });
        board[endX][endY] = std::shared_ptr<Square>(new Square{ endX, endY, sizeX + sizeY, sizeX + sizeY,  SquareState::TRAVERSABLE });
        board[2][1] = std::shared_ptr<Square>(new Square{ 2, 1, sizeX + sizeY, sizeX + sizeY,  SquareState::UNTRAVERSABLE });
        board[2][2] = std::shared_ptr<Square>(new Square{ 2, 2, sizeX + sizeY, sizeX + sizeY,  SquareState::UNTRAVERSABLE });
        board[1][2] = std::shared_ptr<Square>(new Square{ 2, 2, sizeX + sizeY, sizeX + sizeY,  SquareState::UNTRAVERSABLE });
        std::shared_ptr<Square> cursor = board[startX][startY];
        std::vector<std::shared_ptr<Square>> squareCalculed;
        std::vector<std::shared_ptr<Square>> squareVisited;

        while (cursor->getX() != board[endX][endY]->getX() || cursor->getY() != board[endX][endY]->getY())
        {
            /*Calcul des heuristiques des noeuds voisins*/
            for (int i = -1; i < 2; i = i++)
            {
                for (int j = -1; j < 2; j = j++)
                {
                    if (cursor->getX() + i >= 0 && cursor->getX() + i < sizeX && cursor->getY() + j >= 0 && cursor->getY() + j < sizeY)
                    {
                        std::shared_ptr<Square> target = board[cursor->getX() + i][cursor->getY() + j];
                        if (target->getState() != SquareState::UNTRAVERSABLE && (i != 0 || j != 0))
                        {
                            float newCost = calculCost(cursor, target, board[endX][endY]);
                            if (newCost + cursor->getHeuristic() + 1 < target->getCost()) {
                                target->setCost(cursor->getCost() + newCost);
                                target->setHeuristic(cursor->getHeuristic() + 1);
                            }
                            bool isAlreadyPresent = false;
                            bool isAlreadyVisited = false;
                            for (int x = 0; x < squareCalculed.size(); x++)
                            {
                                if (target == squareCalculed[x])
                                {
                                    isAlreadyPresent = true;
                                }
                            }
                            for (int y = 0; y < squareVisited.size(); y++)
                            {
                                if (target == squareVisited[y])
                                {
                                    isAlreadyVisited = true;
                                }
                            }
                            if (!isAlreadyPresent && !isAlreadyVisited)
                            {
                                squareCalculed.push_back(target);
                            }
                        }
                    }
                }
            }

            /*Recherche des noeuds visit�s avec le cout le plus faible*/
            std::shared_ptr<Square> futureNode = squareCalculed[0];
            int lowestGlobalCost = squareCalculed[0]->getCost() + squareCalculed[0]->getHeuristic();

            for (int i = 0; i < squareCalculed.size(); i++)
            {
                if ((squareCalculed[i]->getCost() + squareCalculed[i]->getHeuristic()) < lowestGlobalCost)
                {
                    futureNode = squareCalculed[i];
                    lowestGlobalCost = squareCalculed[i]->getCost() + squareCalculed[i]->getHeuristic();
                }
            }

            /*Recherche du noeud voisin avec le cout le plus faible*/
            /*int localCost = cursor->getHeuristic();
            std::shared_ptr<Square> futureNode = cursor;
            for (int i = -1; i < 2; i = i++)
            {
                for (int j = -1; j < 2; j = j++)
                {
                    if (cursor->getX() + i < sizeX && cursor->getY() + j < sizeY)
                    {
                        if (board[cursor->getX() + i][cursor->getY() + j]->getHeuristic() < localCost && board[cursor->getX() + i][cursor->getY() + j]->getState() != SquareState::UNTRAVERSABLE)
                        {
                            localCost = board[cursor->getX() + i][cursor->getY() + j]->getHeuristic();
                            futureNode = board[cursor->getX() + i][cursor->getY() + j];
                        }
                    }
                }
            }*/

            /*D�placement vers le noeud avec le cout le plus faible*/
            squareVisited.push_back(cursor);
            cursor = futureNode;
            for (int i = 0; i < squareCalculed.size(); i++)
            {
                if (cursor == squareCalculed[i])
                {
                    squareCalculed.erase(squareCalculed.begin() + i);
                }
            }
            //Trouver l'index d'un noeud

        }
        // On refait le chemin pour le noter
        std::deque<std::shared_ptr<Square>> path;
        std::shared_ptr<Square> traveler = board[startX][startY];
        path.push_back(traveler);

        for (int test = 0; test < 5; test++)
            /*while (traveler->getX() != board[endX][endY]->getX() || traveler->getY() != board[endX][endY]->getY())*/
        {
            std::deque<std::shared_ptr<Square>> voisins = neighbours(traveler->getX(), traveler->getX());
            std::cout << traveler->getX() << ',' << traveler->getY() << std::endl;

            float lowestCost = voisins[0]->getCost();
            int lowestHeuristic = voisins[0]->getHeuristic();
            std::shared_ptr<Square> nextStep = voisins[0];

            for (auto v : voisins)
            {
                float vCost = v->getCost();
                int vHeuristic = v->getHeuristic();

                if ((vCost < lowestCost) || (vCost == lowestCost && vHeuristic < lowestHeuristic))
                {
                    nextStep = v;
                    lowestCost = vCost;
                    lowestHeuristic = vHeuristic;
                }
            }
            traveler = nextStep;
            path.push_back(nextStep);

            for (auto i : path)
            {
                std::cout << i->getX() << ',' << i->getY() << std::endl;
            }
        }
        path.push_back(board[endX][endY]);
        return path;
    }
    /*
    * On compare la distance entre s1 et dest et s2 et dest
    * Si s1 est plus pr�s que s2 -> 1
    * Si s1 est plus pr�s que s2 -> 0
    * Si s1 est plus pr�s que s2 -> 1
    */
    float calculCost(std::shared_ptr<Square> s1, std::shared_ptr<Square> s2, std::shared_ptr<Square> dest)
    {
        int diffS1X = abs(dest->getX() - s1->getX());
        int diffS2X = abs(dest->getX() - s2->getX());
        int diffS1Y = abs(dest->getY() - s1->getY());
        int diffS2Y = abs(dest->getY() - s2->getY());
        if (diffS1X < diffS2X && diffS1Y < diffS2Y)
        {
            return (float)sqrt(2);
        }
        else if (diffS1X < diffS2X && diffS1Y == diffS2Y || diffS1X == diffS2X && diffS1Y < diffS2Y)
        {
            return 1.0f;
        }
        else if (diffS1X > diffS2X && diffS1Y < diffS2Y || diffS1X < diffS2X && diffS1Y > diffS2Y)
        {
            return 0.0f;
        }
        else if (diffS1X > diffS2X && diffS1Y > diffS2Y)
        {
            return (float)-sqrt(2);
        }
        else
        {
            return -1.0;
        }
    }

    std::deque<std::shared_ptr<Square>> neighbours(int squareX, int squareY)
    {
        std::deque<std::shared_ptr<Square>> ptrNeighboursList;

        /*switch (squareX)
        {
        case 0:
            addChessboardCase(NORTH);
            break;
        case sizeX:
            addChessboardCase(SOUTH);
            break;
        }

        switch (squareY)
        {
        case 0:
            addChessboardCase(WEST);
            break;
        case sizeY:
            addChessboardCase(EAST);
            break;
        }*/

        for (int i = -1; i < 2; i = i++)
        {
            for (int j = -1; j < 2; j = j++)
            {
                if (squareX + i >= 0 && squareX + i < sizeX && squareY + j >= 0 && squareY + j < sizeY)
                {
                    if (i != 0 && j != 0)
                    {
                        ptrNeighboursList.push_back(board[squareX + i][squareY + j]);
                    }
                }
            }
        }

        return ptrNeighboursList;
    }
protected:
    void shiftColumns()
    {
        for (std::deque<std::shared_ptr<Square>> row : board)
        {
            for (std::shared_ptr<Square> square : row)
            {
                square->setY(square->getY() + 1);
            }
        }
    }
    void shiftLines()
    {
        for (std::deque<std::shared_ptr<Square>> row : board)
        {
            for (std::shared_ptr<Square> square : row)
            {
                square->setX(square->getX() + 1);
            }
        }
    }
    void shiftLinesAndColumns()
    {
        for (std::deque<std::shared_ptr<Square>> row : board)
        {
            for (std::shared_ptr<Square> square : row)
            {
                square->setX(square->getX() + 1);
                square->setY(square->getY() + 1);
            }
        }
    }
private:
    int sizeX;
    int sizeY;
    std::deque<std::deque<std::shared_ptr<Square>>> board;
};

int main()
{
    std::shared_ptr<Board> board = std::shared_ptr<Board>(new Board(10, 10));
    board->addChessboardCase(SOUTH_EAST);
    board->printChessboard();
    int startX = 1;
    int startY = 1;
    int endX = 4;
    int endY = 4;
    std::deque<std::shared_ptr<Square>> cheminTest = board->searchShortestPath(startX, startY, endX, endY);
    std::cout << "Chemin recommande pour aller de  (" << startX << "," << startY << ") a (" << endX << "," << endY << ") : \n";
    for (auto i : cheminTest)
    {
        std::cout << "  ( " << i->getX() << " , " << i->getY() << " ) \n";
    }
    std::cout << " \n" << std::endl;

}