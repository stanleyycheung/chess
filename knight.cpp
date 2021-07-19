#include "knight.h"

Knight::Knight(int colour, Square position) : ChessPiece(colour, position)
{
    symbol = (colour == WHITE) ? W_KNIGHT : B_KNIGHT;
    name = "Knight";
}

std::vector<Square> Knight::getMoveSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE])
{
    std::vector<Square> validMoves;
    Square topTopLeft = Square(N) + Square(N) + Square(W);
    Square topLeft = Square(N) + Square(W) + Square(W);
    Square bottomBottomLeft = Square(S) + Square(S) + Square(W);
    Square bottomLeft = Square(S) + Square(W) + Square(W);

    Square topTopRight = Square(N) + Square(N) + Square(E);
    Square topRight = Square(N) + Square(E) + Square(E);
    Square bottomBottomRight = Square(S) + Square(S) + Square(E);
    Square bottomRight = Square(S) + Square(E) + Square(E);

    Square directions[] = {topTopLeft, topLeft, bottomBottomLeft, bottomLeft, topTopRight, topRight, bottomBottomRight, bottomRight};

    for (Square unit : directions)
    {
        Square toSquare = position + unit;
        getSquares(toSquare, validMoves, board);
    }
    return validMoves;
}

std::vector<Square> Knight::getAttackSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE])
{
    return getMoveSquares(board);
}
