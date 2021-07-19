#include "pawn.h"

Pawn::Pawn(int colour, Square position) : ChessPiece(colour, position)
{
    symbol = (colour == WHITE) ? W_PAWN : B_PAWN;
    name = "Pawn";
}

std::vector<Square> Pawn::getMoveSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE])
{
    std::vector<Square> validMoves;
    Square localNorth = Square(DIRECTION::N).orient(colour);
    Square nextSquare = position + localNorth;
    if (board[nextSquare.x][nextSquare.y] != nullptr)
    {
        return validMoves;
    }
    Square nextNextSquare = position + localNorth;
    getSquares(nextNextSquare, validMoves, board);
    if (!hasMoved)
    {
        getSquares(position + localNorth + localNorth, validMoves, board);
    }
    return validMoves;
}

std::vector<Square> Pawn::getAttackSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE])
{
    std::vector<Square> validAttacks;
    Square localNE = Square(DIRECTION::NE).orient(colour);
    Square localNW = Square(DIRECTION::NW).orient(colour);
    getSquares(position + localNE, validAttacks, board);
    getSquares(position + localNW, validAttacks, board);
    return validAttacks;
}
