#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BOARD_SIZE 8
#define WHITE 1
#define BLACK -1

const std::string W_KING = "\u2654";
const std::string W_QUEEN = "\u2655";
const std::string W_ROOK = "\u2656";
const std::string W_BISHOP = "\u2657";
const std::string W_KNIGHT = "\u2658";
const std::string W_PAWN = "\u2659";

const std::string B_KING = "\u265A";
const std::string B_QUEEN = "\u265B";
const std::string B_ROOK = "\u265C";
const std::string B_BISHOP = "\u265D";
const std::string B_KNIGHT = "\u265E";
const std::string B_PAWN = "\u265F";

enum DIRECTION
{
    N,
    NE,
    E,
    SE,
    S,
    SW,
    W,
    NW
};


#endif