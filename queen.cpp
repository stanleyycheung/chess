#include "queen.h"

Queen::Queen(int colour, Square position) : ChessPiece(colour, position)
{
    symbol = (colour == WHITE) ? W_QUEEN : B_QUEEN;
    name = "Queen";
}

std::vector<Square> Queen::getMoveSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE])
{
    std::vector<Square> validMoves;
    Square directions[] = {Square(N), Square(E), Square(S), Square(W), Square(NE), Square(NW), Square(SE), Square(SW)};
    for (Square unit : directions)
    {
        int distance = 1;
        bool addedMove = false;
        Square toSquare = position + unit * distance;
        do
        {
            toSquare = position + unit * distance;
            addedMove = getSquares(toSquare, validMoves, board);
            distance++;
        } while (addedMove && board[toSquare.x][toSquare.y] == nullptr);
    }
    return validMoves;
}

std::vector<Square> Queen::getAttackSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE])
{
    return getMoveSquares(board);
}
