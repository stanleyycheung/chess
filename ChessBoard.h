#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <string>
#include "constants.h"
#include "ChessPiece.h"

class ChessBoard
{
private:
    ChessPiece *board[BOARD_SIZE][BOARD_SIZE];
    int turn;

    void printRowKey();
    void printRowFrame();

    void movePiece(Square fromSquare, Square toSquare);

    void setBoard();
    void clearBoard();

    bool validMove(Square fromSquare, Square toSquare);
    bool validAttack(Square fromSquare, Square toSquare);
    bool ifMoveInCheck(Square fromSquare, Square toSquare);
    bool kingIfInCheck(int colour);
    bool haveValidMove(int turn);
    bool validMoveString(std::string move);
    void changeTurn();

    ChessPiece *getPiece(Square square);
    int getTurn();
    std::string getTurnString();
    std::string getOpponentTurnString();

public:
    ChessBoard();
    ~ChessBoard();
    void submitMove(std::string fromStr, std::string toStr);
    void resetBoard();
    void printBoard();
};

#endif