#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
    Queen(int colour, Square c);
    std::vector<Square> getMoveSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE]) override;
    std::vector<Square> getAttackSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE]) override;
};

#endif