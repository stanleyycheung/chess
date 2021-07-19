#include "square.h"

using namespace std;

Square::Square(std::string moveString)
{
    x = BOARD_SIZE - (toupper(moveString[1]) - '1') - 1;
    y = toupper(moveString[0]) - 'A';
}

Square::Square(DIRECTION d)
{
    switch (d)
    {
    case N:
        x = -1;
        y = 0;
        break;
    case E:
        x = 0;
        y = 1;
        break;
    case S:
        x = 1;
        y = 0;
        break;
    case W:
        x = 0;
        y = -1;
        break;
    case NE:
        x = -1;
        y = 1;
        break;
    case SE:
        x = 1;
        y = 1;
        break;
    case SW:
        x = 1;
        y = -1;
        break;
    case NW:
        x = -1;
        y = -1;
        break;
    }
}

Square Square::operator+(Square const &other)
{
    return Square(x + other.x, y + other.y);
}

bool Square::operator==(Square const &other)
{
    return ((x == other.x) && (y == other.y));
}

Square operator*(Square const &square, int const &scalar)
{
    return Square(square.x * scalar, square.y * scalar);
}

Square Square::orient(int colour)
{
    return Square(x * colour, y * colour);
}

std::string Square::squareRepresentation()
{
    char y_char = y + 'A';
    char x_char = BOARD_SIZE - 1 - x + '1';
    std::string output = std::string() + y_char + x_char;
    return output;
}

ostream &operator<<(ostream &o, Square const &coord)
{
    return o << "(" << coord.x << "," << coord.y << ")";
}
