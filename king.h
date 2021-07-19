#ifndef KING_H
#define KING_H

#include "ChessPiece.h"

class King : public ChessPiece
{
public:
    King(int colour, Square c);
    std::vector<Square> getMoveSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE]) override;
    std::vector<Square> getAttackSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE]) override;
};

#endif