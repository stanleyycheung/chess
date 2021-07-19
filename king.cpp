#include "king.h"

King::King(int colour, Square position) : ChessPiece(colour, position)
{
    symbol = (colour == WHITE) ? W_KING : B_KING;
    name = "King";
}

std::vector<Square> King::getMoveSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE])
{
    std::vector<Square> validMoves;
    Square directions[] = {Square(N), Square(E), Square(S), Square(W), Square(NE), Square(NW), Square(SE), Square(SW)};
    for (Square unit : directions)
    {
        Square toSquare = position + unit;
        getSquares(toSquare, validMoves, board);
    }
    return validMoves;
}

std::vector<Square> King::getAttackSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE])
{
    return getMoveSquares(board);
}
