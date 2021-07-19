#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
    Knight(int colour, Square c);
    std::vector<Square> getMoveSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE]) override;
    std::vector<Square> getAttackSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE]) override;
};

#endif