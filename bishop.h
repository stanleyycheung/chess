#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : public ChessPiece {
    public:
        Bishop (int colour, Square c);
        std::vector<Square> getMoveSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE]) override;
        std::vector<Square> getAttackSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE]) override;
};

#endif