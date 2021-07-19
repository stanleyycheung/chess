#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
    Pawn(int colour, Square c);
    std::vector<Square> getMoveSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE]) override;
    std::vector<Square> getAttackSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE]) override;
};

#endif