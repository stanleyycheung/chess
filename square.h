#ifndef COORDINATES_H
#define COORDINATES_H

#include <iostream>
#include <string>
#include "constants.h"

struct Square
{
    int x;
    int y;

    Square(int x, int y) : x(x), y(y) {}
    Square(std::string moveString);
    Square(DIRECTION d);

    Square operator+(Square const &other);
    bool operator==(Square const &other);
    friend Square operator*(Square const &square, int const &scalar);
    Square orient(int colour);
    std::string squareRepresentation();

    friend std::ostream &operator<<(std::ostream &o, Square const &coord);
};

#endif