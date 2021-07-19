#include "bishop.h"

Bishop::Bishop(int colour, Square position) : ChessPiece(colour, position)
{
    symbol = (colour == WHITE) ? W_BISHOP : B_BISHOP;
    name = "Bishop";
}

std::vector<Square> Bishop::getMoveSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE])
{
    std::vector<Square> validMoves;
    Square directions[] = {Square(NE), Square(NW), Square(SE), Square(SW)};
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

std::vector<Square> Bishop::getAttackSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE])
{
    return getMoveSquares(board);
}
