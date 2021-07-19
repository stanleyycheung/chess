#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>
#include <vector>
#include "square.h"
#include "constants.h"

class ChessPiece
{
protected:
    int colour;
    std::string symbol;
    std::string name;
    Square position;
    bool hasMoved = false;

public:
    ChessPiece(int colour, Square position) : colour(colour), position(position) {}
    virtual ~ChessPiece(){};
    virtual std::vector<Square> getMoveSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE]) = 0;
    virtual std::vector<Square> getAttackSquares(ChessPiece *board[BOARD_SIZE][BOARD_SIZE]) = 0;

    bool getSquares(Square toSquare, std::vector<Square> &validMoves, ChessPiece *board[BOARD_SIZE][BOARD_SIZE])
    {
        if (toSquare.x < 0 || toSquare.y < 0 || toSquare.x >= BOARD_SIZE || toSquare.y >= BOARD_SIZE)
        {
            return false;
        }
        
        if (board[toSquare.x][toSquare.y] != nullptr && board[toSquare.x][toSquare.y]->colour == this->colour)
        {
            return false;
        }
        validMoves.push_back(toSquare);
        return true;
    }

    int getColour()
    {
        return colour;
    }
    std::string getColourString()
    {
        if (colour == WHITE)
        {
            return "White";
        }
        else
        {
            return "Black";
        }
    }
    std::string getSymbol()
    {
        return symbol;
    }

    std::string getName()
    {
        return name;
    }

    Square getPosition()
    {
        return position;
    }

    std::string getInfo()
    {
        std::string colour_str;
        if (colour == 1)
        {
            colour_str = "White";
        }
        else
            colour_str = "Black";
        return colour_str + "'s " + name + " at " + position.squareRepresentation();
    }

    bool getHasMoved()
    {
        return hasMoved;
    }

    void setMoved()
    {
        hasMoved = true;
    }

    void setPosition(Square square)
    {
        position = square;
    }

    friend std::ostream &operator<<(std::ostream &o, ChessPiece *const piece)
    {
        if (piece == nullptr)
        {
            return o << " ";
        }
        return o << piece->getSymbol();
    }
};

#endif